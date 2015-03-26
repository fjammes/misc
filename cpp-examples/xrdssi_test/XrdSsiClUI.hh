#ifndef __XRDSSICLUI_HH__
#define __XRDSSICLUI_HH__
/******************************************************************************/
/*                                                                            */
/*                         X r d S s i C l U I . h h                          */
/*                                                                            */
/* (c) 2014 by the Board of Trustees of the Leland Stanford, Jr., University  */
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

#include "XrdOuc/XrdOucStream.hh"
#include "XrdSys/XrdSysPthread.hh"

class XrdSsiService;
class XrdSsiSession;

class XrdSsiClUI
{
public:

enum Action   {CancelRequest=0, Provision,   Reprovision,
               SendRequest,     StopService, Unprovision};

void           AddSession(const char *sName, XrdSsiSession *sP);

void           DelSession(const char *sName);

Action         GetRequest(int &reqLen);

bool           ParseCL(int argc, char **argv);

char          *cmdName;
const char    *contact;
char          *sessName;
int            timeOut;
int            readSZ;
bool           isAsync;
bool           doEcho;
XrdSsiService *ssiService;
XrdSsiSession *ssiSession;
char          *reqBuff;

               XrdSsiClUI();
              ~XrdSsiClUI() {}
private:

struct Session
      {char          *sessN;
       XrdSsiSession *sessP;
       Session       *next;
                      Session(char *sn, XrdSsiSession *sp, Session *pp)
                             : sessN(sn), sessP(sp), next(pp) {}
                     ~Session() {free(sessN);}
      };

bool           DoSess();
void           DoSet();
void           DoSource();
Session       *FindSession(const char *sname, Session **psP=0);
bool           GetNum(const char *opT, char *opV, int &opD);
long long      GetSize(const char *tName, char *var, long long maxV);
char          *GetToken(const char *tName);
void           Help();
bool           Usage();
Session       *sessList;
char          *iSession;

XrdSysMutex    uiMutex;
XrdOucStream   cLine;
char           prompt[80];
static const   int minBsz = 1024;        // 1 KB
static const   int maxBsz = 8*1024*1024; // 8 MB
int            reqBsz;
int            reqBpad;
int            srcFD;
};
#endif
