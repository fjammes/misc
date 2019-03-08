/******************************************************************************/
/*                                                                            */
/*                    X r d S s i S v S e r v i c e . c c                     */
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

#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "XrdNet/XrdNetAddr.hh"

#include "XrdSsi/XrdSsiCluster.hh"
#include "XrdSsi/XrdSsiLogger.hh"

#include "XrdSsiSvService.hh"
#include "XrdSsiSvSession.hh"

/******************************************************************************/
/*                               G l o b a l s                                */
/******************************************************************************/
  
namespace XrdSsiSv
{
XrdSsiLogger  *mDest;           // Object to use for mesages
XrdSsiCluster *Cluster;         // Object to use to control the cluster
XrdNetAddr     myAddr((int)0);  // A way to get our host name for testing
}

/******************************************************************************/
/*                X r d S s i G e t S e r v e r S e r v i c e                 */
/******************************************************************************/
  
/*! This is called during server initialization to get our particular
    service. The directive "xrootd.fslib" states the path to the shared
    library that contains this code.
*/
extern "C"
{
XrdSsiService *XrdSsiGetServerService(XrdSsiLogger  *logP,
                                      XrdSsiCluster *clsP,
                                      const char    *cfgFn,
                                      const char    *parms)
{
// We don't process a configuration file nor have any parameters, so we will
// ingnore those two parameters. We will, however, record the log and cluster
// pointers in a globally accessible area in our own namespace. Then return an
// instance of out object.
//
   XrdSsiSv::mDest   = logP;
   XrdSsiSv::Cluster = clsP;
   return new XrdSsiSvService;
}
}

/******************************************************************************/
/*                             P r o v i s i o n                              */
/******************************************************************************/
  
bool XrdSsiSvService::Provision(XrdSsiService::Resource *resP,
                                unsigned short           timeOut
                               )
{
// Note that on the server, arguments resP->hAvoid and argument timeout are
// meaningless and always set to zero. So, we ignore these. The static here
// is to test some features that server-side provision has. The resource name
// simply becomes our session name.
//
   static int busyCount = 0;
   const char *rDest, *sName = resP->rName;

// We test the "busy" return. A session of "/.../busy" triggers this and
// eventualy we will fail the provision. We ignore MT issues for this.
//
   if (strstr(sName, "/busy"))
      {busyCount++;
       if (busyCount & 0x3) resP->eInfo.Set("Testing busy return...", EBUSY, 3);
          else resP->eInfo.Set("Resource not available.", EINTR);
       return false;
      }

// Here we test how the client recovers from an ENOENT. In the presence of a
// redirector, the client should seek an alternate endpoint. This is triggered
// if the name of the file has our host name.
//
   if (strstr(sName, XrdSsiSv::myAddr.Name("???")))
      {resP->eInfo.Set("Session name not found.", ENOENT);
       return false;
      }

// Here we test redirection. This is triggered by a session name that contains
// ">hostname:port"; the client is redirected to hostname:port
//
   if ((rDest = index(sName, '>')))
      {const char *Colon = rindex(rDest+1, ':');
       char hdest[256];
       int port = 0, hlen = 0;
       if (Colon)
          {port = atoi(Colon+1);
           hlen = Colon - rDest - 1;
          }
       if (port <= 0 || !hlen || hlen >= (int)sizeof(hdest))
          {resP->eInfo.Set("Invalid redirect destination.", EINVAL);
           return false;
          }
       strncpy(hdest, rDest+1, hlen); hdest[hlen] = 0;
       resP->eInfo.Set(hdest, EAGAIN, port);
       return false;
      }

// We have cleared all the hurdles, so return a sesion object. If we wanted to
// be efficient we would have a pool of session objects ready for reuse, sigh.
//
   resP->ProvisionDone(new XrdSsiSvSession(sName));
   return true;
}
