#ifndef __XRDSSISVSESSION_HH__
#define __XRDSSISVSESSION_HH__
/******************************************************************************/
/*                                                                            */
/*                    X r d S s i S v S e s s i o n . h h                     */
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

#include "XrdSsi/XrdSsiResponder.hh"
#include "XrdSsi/XrdSsiSession.hh"

// Here we define out session implementation. We need to inherit the Session
// class but equally important we need to also inherit the Respond class in
// order to post a response to the request object.

class XrdSsiSvSession : public XrdSsiSession, public XrdSsiResponder
{
public:

//-----------------------------------------------------------------------------
//! Process a new request (on server-side a new thread is used for this call).
//-----------------------------------------------------------------------------

        bool   ProcessRequest(XrdSsiRequest *reqP, unsigned short tOut=0);

//-----------------------------------------------------------------------------
//! Unprovision a session. 
//-----------------------------------------------------------------------------

        bool   Unprovision(bool forced=false);

//-----------------------------------------------------------------------------
//! Constructor
//-----------------------------------------------------------------------------

               XrdSsiSvSession(const char *sname, char *sloc=0)
                              : XrdSsiSession(strdup(sname), sloc),
                                XrdSsiResponder(this, (void *)0),
                                streamRdSz(0), streamActv(false),
                                isActive(false) {}

protected:

//-----------------------------------------------------------------------------
//! Notify a session that a request either completed or was canceled. This
//! method allows the session to release any resources given to the request
//! object (e.g. data response buffer or a stream) before it looses control.
//-----------------------------------------------------------------------------

        void   RequestFinished(      XrdSsiRequest  *rqstP,
                               const XrdSsiRespInfo &rInfo,
                                     bool            cancel=false);

//-----------------------------------------------------------------------------
//! Destructor is protected. You cannot use delete on a session, use 
//! Unprovision() to effectively delete the session object.
//-----------------------------------------------------------------------------

              ~XrdSsiSvSession() {if (sessName) free(sessName);}
private:
bool           Respond(const char *rData, int rLen=-1);
bool           RespondErr(XrdSsiResponder::Status rc);

char           respBuff[1024];
int            streamRdSz;
bool           streamActv;
bool           isActive;
};
#endif
