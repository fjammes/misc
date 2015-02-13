/******************************************************************************/
/*                                                                            */
/*                       X r d S s i C l M a i n . c c                        */
/*                                                                            */
/* (c) 2009 by the Board of Trustees of the Leland Stanford, Jr., University  */
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

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "XrdSsiClUI.hh"
#include "XrdSys/XrdSysPthread.hh"

#include "XrdSsi/XrdSsiErrInfo.hh"
#include "XrdSsi/XrdSsiRequest.hh"
#include "XrdSsi/XrdSsiService.hh"
#include "XrdSsi/XrdSsiSession.hh"
#include "XrdSsi/XrdSsiStream.hh"

using namespace std;

/******************************************************************************/
/*                               D e f i n e s                                */
/******************************************************************************/
  
#define verSession if (!clUI.ssiSession) \
                      {cerr << "There is no active session!" <<endl; break;}

#define FATAL(x) {cerr <<"ssicl: " <<x <<endl; exit(3);}

/******************************************************************************/
/*                       N a m e s p a c e   I t e m s                        */
/******************************************************************************/
  
namespace XrdSsiCl
{
const char *cmdName = "ssicl: ";

FILE       *outErr  = fdopen(2, "w");

FILE       *outFile = outErr;
}

/******************************************************************************/
/*                      F i l e   L o c a l   I t e m s                       */
/******************************************************************************/
  
namespace
{
   XrdSysMutex    gMutex;

   XrdSsiClUI     clUI;
}

/******************************************************************************/
/*                        R e q u e s t   O b j e c t                         */
/******************************************************************************/
  
// Generally, a request is associated with some context. Hence, it is required
// that a service specific context object inherit the request object. The
// derived object is upcast when passed to XrdSsiSession::ProcessRequest().
// When the request is accepted, the request object's ProcessResponse() is
// called to handle the response within the appropriate context. In our
// service case we have little to do but you should be able to get the idea.
//
class myRequest : public XrdSsiRequest
{
public:

void    Cancel();

char   *GetRequest(int &dlen) {dlen = reqBlen; return reqBuff;}

bool    ProcessResponse(const XrdSsiRespInfo &rInfo, bool isOK=true);

void    ProcessResponseData(char *buff, int dlen, bool last);

void    RelRequestBuffer() {if (reqBuff) free(reqBuff); reqBuff = 0;}

        myRequest(char *buff, int blen)
                 : reqBuff(buff), reqBlen(blen), cancelled(false), totbytes(0)
                    {readSZ = (clUI.readSZ > (int)sizeof(rspBuff)
                            ?  sizeof(rspBuff) : clUI.readSZ);
                     gMutex.Lock();
                     currentRequest = this;
                     gMutex.UnLock();
                    }
       ~myRequest() {if (reqBuff) free(reqBuff);
                     gMutex.Lock();
                     if (currentRequest == this) currentRequest = 0;
                     gMutex.UnLock();
                    }

static myRequest *currentRequest;

private:
char *reqBuff;
int   reqBlen;
int   totbytes;
int   readSZ;
char  rspBuff[1024*1024];
bool  cancelled;
};

myRequest *myRequest::currentRequest = 0;  // Pointer to current request

/******************************************************************************/
/*                     m y R e q u e s t : : C a n c e l                      */
/******************************************************************************/
  
void myRequest::Cancel()
{
   bool finStatus;

// First mark that we were cancelled to avoid calling finished twice.
//
   cancelled = true;

// Now tell the request we are done because we want to cancel it
//
   finStatus = Finished(true);

// Now if tyhe cancel was not accepted then someone else got to call
// finish first. Be aware this is only for testing as we are not doing proper
// locking to avoid refering to a deleted object.
//
   if (finStatus) fprintf(XrdSsiCl::outErr,"Current request cancelled.\n");
      else        fprintf(XrdSsiCl::outErr,"Request not cancelled, no longer valid.\n");
}

/******************************************************************************/
/*            m y R e q u e s t : : P r o c e s s R e s p o n s e             */
/******************************************************************************/

bool myRequest::ProcessResponse(const XrdSsiRespInfo &rInfo, bool isOK)
{
   static const char *respName[] = {"isNone", "isData", "isError",
                                    "isFile", "isStream"};
   const char *sName = GetSession()->Name();
   int eCode;

// Check if processing completed correctly, If not, issue message and delete
// the request object (i.e. ourselves).
//
   if (!isOK)
      {fprintf(XrdSsiCl::outFile, "Request %s@%s failed; %s\n", sName,
               clUI.contact, eInfo.Get(eCode));
       Finished();
       delete this;
       return true;
      }

// We do some debugging here
//
   fprintf(XrdSsiCl::outFile, "Received %s response from %s@%s\n",
           respName[rInfo.rType], sName, clUI.contact);

// While a response can have one of several forms a good response can only be
// isStream as the framework converts any non-error server response to a passive
// stream for the client. The isError response is always reflected in our eInfo
// object for consistency (though it may be present here if the server sent it).
// This allows us to use the async helper GetResponseData() without fussing.
//
   if (GetResponseData(rspBuff, readSZ)) return true;

// So, we failed, print an error, finish the request, and get out of here.
//
   fprintf(XrdSsiCl::outFile, "Unable to get initial data from session "
           "%s@%s; %s\n", sName, clUI.contact, eInfo.Get(eCode));

   Finished();
   delete this;
   return true;
}

/******************************************************************************/

void myRequest::ProcessResponseData(char *buff, int dlen, bool last)
{
   const char *sName = GetSession()->Name();
   int eCode;

// Check if the request for response data ended with an error. If so, we tell
// the session we are finished with this request and delete simply ourselves.
//
   if (dlen < 0)
      {fprintf(XrdSsiCl::outFile, "Unable to get data from session "
               "%s@%s; %s\n", sName, clUI.contact, eInfo.Get(eCode));
       Finished();
       delete this;
       return;
      }

// Display the data if we actually have some.
//
   if (dlen > 0)
      {totbytes += dlen;
       if (clUI.doEcho) fwrite(buff, dlen, 1, XrdSsiCl::outFile);
      }

// Now we check if we need to ask for more data. If last is false, we do!
//
   if (!last)
      {if (GetResponseData(rspBuff, readSZ)) return;
       fprintf(XrdSsiCl::outFile, "Unable to get more data from session "
               "%s@%s; %s\n", sName, clUI.contact, eInfo.Get(eCode));
      }

// End with new line character
//
   fprintf(XrdSsiCl::outFile, "\nRecieved %d bytes from %s@%s\n",
                              totbytes, sName, clUI.contact);

// We are done with our request. We avoid calling Finished if we got here
// because we were cancelled.
//
   Finished();
   delete this;
}

/******************************************************************************/
/*                             P r o v i s i o n                              */
/******************************************************************************/

// The following class is used to define a resource object with an actual
// callback implementation. This is needed when we provision a session.
// This object also handles reprovisioning.

class SessionResource : public XrdSsiService::Resource
{
public:
void  ProvisionDone(XrdSsiSession *sessP);

      SessionResource(const char *rname, XrdSsiSession *oldSess=0)
                     : Resource(0), oldsP(oldSess)
                     {rDup = strdup(rname); rName = rDup;
                      if (oldSess) hAvoid = oldSess->Location();
                     }

     ~SessionResource() {if (rDup) free(rDup);}
private:
char          *rDup;
XrdSsiSession *oldsP;
};

void SessionResource::ProvisionDone(XrdSsiSession *sessP)
{
// If we have no session then issue an error message. We use a common method to
// allow the Provision() caller display the error without duplicating code.
// Otherwise, we display tell the user we have one and add it to the UI.
// If we have an old session then we unprovision it now, remove it and add
// back the new one.
//
   if (sessP)
      {fprintf(XrdSsiCl::outFile, "Session %s provisioned.\n", rName);
       if (oldsP)
          {if (!oldsP->Unprovision())
              {fprintf(XrdSsiCl::outErr, "Unable to reprovision session %s; "
                                         "requests active.\n", oldsP->Name());
               sessP->Unprovision();
               delete this;
               return;
              }
           clUI.DelSession(rName);
          }
       clUI.AddSession(rName, sessP);
      } else {
       int eNum;
       fprintf(XrdSsiCl::outFile, "Provision %s failed; %s\n", rName,
                                  eInfo.Get(eNum));
      }

// We are done, so we can delete ourselves
//
   delete this;
}
  
/******************************************************************************/

void Provision(char *rName)
{
// Instantiate an instance of the resource object for provisioning
//
   SessionResource *sessionResource = new SessionResource(rName);

// The following obtains a new session with name with resource rName (passed).
// If we succeed then the callback (see above) will add the session to the UI.
//
   if (!clUI.ssiService->Provision(sessionResource, clUI.timeOut))
      {int eNum;
       fprintf(XrdSsiCl::outErr, "Provision %s failed; %s\n", rName,
                                 sessionResource->eInfo.Get(eNum));
       delete sessionResource;
      }
}

/******************************************************************************/
/*                           R e p r o v i s i o n                            */
/******************************************************************************/
  
void Reprovision()
{
   SessionResource *sessionResource;
   const char *rName = clUI.ssiSession->Name();

// Reprovisioning is a manual process. We want a new session that avoids using
// the current session's endpoint. The session resource object will set this
// up by setting hAvoid in the resource when it sees we have a current session.
//
   sessionResource = new SessionResource(rName, clUI.ssiSession);

// Get a new session. Upon success the callback will unprovision the old session
//
   if (!clUI.ssiService->Provision(sessionResource, clUI.timeOut))
      {int eNum;
       fprintf(XrdSsiCl::outErr, "Reprovision %s failed; %s\n", rName,
                                 sessionResource->eInfo.Get(eNum));
       delete sessionResource;
      }
}

/******************************************************************************/
/*                           S e n d R e q u e s t                            */
/******************************************************************************/
  
void SendRequest(char *reqData, int reqLen)
{
  XrdSsiRespInfo rInfo;
  XrdSsiErrInfo  eInfo;
  myRequest     *reqP;
  int            eCode;
  bool           isOK;

// Normally, we would maintain a pool of request objects to avoid new/delete
// calls. For our simple client we have no context so we simply always get a
// new object.
//
   reqP = new myRequest(reqData, reqLen);

// We simply hand off the request to the session to deal with it. When a
// response is ready or an error occured our callback is invoked which simply
// posts a semaphore telling us the response is ready or an error occurred.
//
   isOK = clUI.ssiSession->ProcessRequest(reqP, clUI.timeOut);

// Check if processing completed correctly, If not, issue message and delete
// the request object. No need to call Finish() as the request never started.
//
   if (!isOK)
      {fprintf(XrdSsiCl::outErr, "Unable to send request to %s@%s; %s\n",
               clUI.sessName, clUI.contact, reqP->eInfo.Get(eCode));
//     reqP->Finished();
       delete reqP;
      }
}

/******************************************************************************/
/*                                  m a i n                                   */
/******************************************************************************/
  
int main(int argc, char **argv)
{
   XrdSsiErrInfo     eInfo;
   int               eCode, reqLen;

// Parse the command line and get the options
//
   if (!clUI.ParseCL(argc, argv)) exit(1);

//** The first step is to allocate a service object. Potentially, we can have
//   many such service objects, each with a different contat. Here we need to
//   have only one for this program.
//
   if (!(clUI.ssiService = XrdSsiGetClientService(eInfo, clUI.contact)))
      {fprintf(XrdSsiCl::outErr, "Unable to get service object for %s; %s\n",
                                 clUI.contact, eInfo.Get(eCode));
       exit(3);
      }

// Make sure all output is unbuffered
//
  setbuf(XrdSsiCl::outFile, 0);
  setbuf(XrdSsiCl::outErr,  0);

// Now we simply get input commands and dispatch then as needed. Return value
// is the operation that needs to be performed.
//
   while(1)
        {switch(clUI.GetRequest(reqLen))
           {case XrdSsiClUI::Provision:
                             Provision(clUI.reqBuff);
                             break;
            case XrdSsiClUI::Unprovision:
                             verSession;
                             if (clUI.ssiSession->Unprovision())
                                {clUI.ssiSession = 0;
                                 clUI.DelSession(clUI.sessName);
                                } else {
                                 fprintf(XrdSsiCl::outErr,
                                         "Unable to unprovision session %s; "
                                         "requests active.\n", clUI.sessName);
                                }
                             break;
            case XrdSsiClUI::Reprovision:
                             verSession;
                             Reprovision();
                             break;
            case XrdSsiClUI::SendRequest:
                             verSession;
                             SendRequest(clUI.reqBuff, reqLen);
                             clUI.reqBuff = 0;
                             break;
            case XrdSsiClUI::CancelRequest:
                             verSession;
                             gMutex.Lock();
                             if (myRequest::currentRequest)
                                {myRequest::currentRequest->Cancel();
                                 myRequest::currentRequest = 0;
                                } else fprintf(XrdSsiCl::outErr,
                                             "No current request to cancel.\n");
                             gMutex.UnLock();
                             break;
            case XrdSsiClUI::StopService:
                             if (clUI.ssiService->Stop()) exit(0);
                             fprintf(XrdSsiCl::outErr, "Unable to stop service "
                                     "%s; sessions active.\n", clUI.contact);
                             break;
            default:         break;
           }
        }
}
