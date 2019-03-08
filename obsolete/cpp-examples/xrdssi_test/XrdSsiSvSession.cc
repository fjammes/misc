/******************************************************************************/
/*                                                                            */
/*                    X r d S s i S v S e s s i o n . c c                     */
/*                                                                            */
/* (c) 2013 by the Board of Trustees of the Leland Stanford, Jr., University  */
/*   Produced by Andrew Hanushevsky for Stanford University under contract    */
/*              DE-AC02-76-SFO0515 with the Department of Energy              */
/*                                                                            */
/* This file is part of the XRootD software suite.                            */
/*                                                                            */
/* XRootD is free software: you can redistribute it and/or modify it under    */
/* the terms of the GNU Lesser General Public License as published by the     */
/* Free Software Foundation, either version 3 of the License, or (at your     */
/* option) any later version.                                                 */
/*                                                                            */
/* XRootD is distributed in the hope that it will be useful, but WITHOUT      */
/* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or      */
/* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public       */
/* License for more details.                                                  */
/*                                                                            */
/* You should have received a copy of the GNU Lesser General Public License   */
/* along with XRootD in a file called COPYING.LESSER (LGPL license) and file  */
/* COPYING (GPL license).  If not, see <http://www.gnu.org/licenses/>.        */
/*                                                                            */
/* The copyright holder's institutional names and contributor's names may not */
/* be used to endorse or promote products derived from this software without  */
/* specific prior written permission of the institution or contributor.       */
/******************************************************************************/

#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "XrdOuc/XrdOucTokenizer.hh"
#include "XrdSys/XrdSysTimer.hh"

#include "XrdSsi/XrdSsiErrInfo.hh"
#include "XrdSsi/XrdSsiRequest.hh"

#include "XrdSsiSvSession.hh"
#include "XrdSsiSvStreamActive.hh"
#include "XrdSsiSvStreamPassive.hh"

using namespace std;

/******************************************************************************/
/*                               D e f i n e s                                */
/******************************************************************************/
  
#define TRACE(x) cerr <<sessName <<": " <<x <<endl

/******************************************************************************/
/*                       R e q u e s t F i n i s h e d                        */
/******************************************************************************/
  
void   XrdSsiSvSession::RequestFinished(XrdSsiRequest        *rqstP,
                                        const XrdSsiRespInfo &rInfo,
                                        bool                  cancel)
{
// We are called when the request has completed either because the response
// was finally sent or the client cancelled the request. A request is
// cancelled because the client requested it, unprovisioned the session, or
// we lost the connection to the client. This provides us the opportunity to
// reclaim any resources tied up with the request object.
//
   const char *what = (cancel ? "cancelled" : "completed");

   isActive = false;
   TRACE("Request has been " <<what <<" resp " <<rInfo.State());

// Now free up resources depending on how we responded
//
   switch(rInfo.rType)
         {case XrdSsiRespInfo::isData:
               // We use a fixed buffer. Otherwise, we would release it.
               break;
          case XrdSsiRespInfo::isError:
               // While error messages are copied, the object releases them.
               break;
          case XrdSsiRespInfo::isFile:
               // We responded with a file so we should close it
               TRACE("Closing fd="<<rInfo.fdnum);
               close(rInfo.fdnum);
               break;
          case XrdSsiRespInfo::isStream:
               // If we responded with a stream then delete it now
               TRACE("Deleting stream");
               delete rInfo.strmP;
               break;
          case XrdSsiRespInfo::isNone:
               // If a response has not been posted then we must have
               // cancelled before a response could have been posted.
               break;
          default:
               TRACE("Unknown response type, cannot complete!");
               break;
         }
}

/******************************************************************************/
/*                        P r o c e s s R e q u e s t                         */
/******************************************************************************/

// This method gets called when a request comes in from a client for this
// particular session. There may be many active sessions at the same time.

bool XrdSsiSvSession::ProcessRequest(XrdSsiRequest *rqstP, unsigned short tOut)   // Always 0
{
   XrdSsiResponder::Status respStat;
   XrdOucTokenizer reqInfo(0);
   XrdSsiStream *sP;
   char *reqData, *reqArgs = 0;
   int   reqSize, fd, n;

// We only support one command at a time for this simple example. So, indicate
// an error if we are still busy with the previous one. We ignore MT issues.
//
   if (isActive)
      {rqstP->eInfo.Set("Previous request has not completed.", EALREADY);
       return false;
      }

// We must take ownership of the request. This is crucial as the request needs
// to know its session and the responder needs to know the request target.
// Since the session and respponder are one in the same we don't specify the
// responder as the third argument.
//
   BindRequest(rqstP, this);

// OK, we are ready to go, get the request and display it
//
   reqData = rqstP->GetRequest(reqSize);
   TRACE(reqSize <<" byte request: " <<reqData);

// Attach the request buffer to our tokenizer (here requests are all ASCII).
//
   reqInfo.Attach(reqData);

// Here we get the first token of the request (the command)
//
   if ((reqData = reqInfo.GetLine())) reqData = reqInfo.GetToken(&reqArgs);
      else {rqstP->eInfo.Set("Request not specified.", EINVAL); return false;}

// Process as needed. We do minimal error checking.
//
   if (!strcmp(reqData, "delay"))
      {int dsec = atoi(reqArgs);
       if (dsec > 0) XrdSysTimer::Snooze(dsec);
       return Respond("Delay completed.");
      }

   if (!strcmp(reqData, "echo" ))
      return Respond(reqArgs);

   if (!strcmp(reqData, "file"))
      {struct stat Stat;
       reqArgs = reqInfo.GetToken();
       if (!reqArgs || !(*reqArgs))
          {rqstP->eInfo.Set("File not specified.", EINVAL); return false;}
       if ((fd = open(reqArgs, O_RDONLY)) < 0 || fstat(fd, &Stat))
          {rqstP->eInfo.Set(0, errno); return false;}
       if (!(respStat = SetResponse(Stat.st_size, fd))) return true;
       return RespondErr(respStat);
      }

   if (!strcmp(reqData, "relbuff" ))
      {ReleaseRequestBuffer();   // Inherited from XrdSsiResponder!
       return Respond("RelBuff() test completed.");
      }

   if (!strcmp(reqData, "stream" ))
      {if (!reqArgs || *reqArgs != '/')
          {char mBuff[80];
                if (reqArgs && !strcmp(reqArgs, "active"))  streamActv = true;
           else if (reqArgs && !strcmp(reqArgs, "passive")) streamActv = false;
           else if (reqArgs) streamRdSz = atoi(reqArgs);
           n = sprintf(mBuff, "stream now %s rdsz %d",
                      (streamActv ? "active" : "passive"), streamRdSz);
           return Respond(mBuff, n);
          }
       if ((fd = open(reqArgs, O_RDONLY)) < 0)
          {rqstP->eInfo.Set(0, errno); return false;}
       if (streamActv) sP = new XrdSsiSvStreamActive (fd, streamRdSz);
          else         sP = new XrdSsiSvStreamPassive(fd, streamRdSz);
       if (!(respStat = SetResponse(sP))) return true;
       return RespondErr(respStat);
      }

// Ok we don't know what this is
//
   rqstP->eInfo.Set("Invalid request.", EINVAL);
   return false;
}

/******************************************************************************/
/*                           U n p r o v i s i o n                            */
/******************************************************************************/

bool XrdSsiSvSession::Unprovision(bool forced)
{
// We are called when the service driver needs to unprovision the session.
// This is only done after Complete() is called on each outstanding request.
// If we are being unprovisioned because the connection was lost, then the
// argument "forced" will be true. In any case, we shouldn't have any requests
// hanging about and it is safe to either recycle ourselves or just do a delete.
// While it's more effecient to reuse ourselves, our simple test service merely
// needs a delete of this session object.
//
   TRACE("unprovisioned!");
   delete this;
}

/******************************************************************************/
/*                        H e l p e r   M e t h o d s                         */
/******************************************************************************/
/******************************************************************************/
/*                               R e s p o n d                                */
/******************************************************************************/
  
bool XrdSsiSvSession::Respond(const char *rData, int rLen)
{
   XrdSsiResponder::Status rc;

// We copy the response into a buffer that must live even after we return to
// the caller because the data in that buffer will be sent back to the client.
//
   if (rLen < 0) rLen = strlen(rData);
   if (rLen < sizeof(respBuff)) strcpy(respBuff, rData);
      else {rLen = sizeof(respBuff) - 1;
            strncpy(respBuff, rData, rLen); respBuff[rLen] = 0;
           }

// We use the inherited method XrdSsiResponder::SetResponse to post the response
// Note we always send the null byte to make it easy on the client :-)
//
   if (!(rc = SetResponse(respBuff, rLen+1))) return true;
   return RespondErr(rc);
}

/******************************************************************************/
/*                            R e s p o n d E r r                             */
/******************************************************************************/
  
bool XrdSsiSvSession::RespondErr(XrdSsiResponder::Status rc)
{
   XrdSsiRequest *rP;
   const char    *why;

// Determine why we could not set a response. This should never happen for our
// simple example as everything is serialized.
//
   switch(rc)
         {case notPosted: why = "duplicate response";
                          break;
          case notActive: why = "request inactive";
                          break;
          default:        why = "unknown error";
                          break;
         }

   TRACE("Response failed; " <<why);
   if ((rP = TheRequest()))
      rP->eInfo.Set("Response protocol failure.", EPROTO);
   return false;
}
