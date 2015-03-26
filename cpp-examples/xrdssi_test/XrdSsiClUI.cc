/******************************************************************************/
/*                                                                            */
/*                         X r d S s i C l U I . c c                          */
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

#include <errno.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "XrdSsi/XrdSsiSession.hh"
#include "XrdSsiClUI.hh"

/******************************************************************************/
/*                       N a m e s p a c e   I t e m s                        */
/******************************************************************************/
  
namespace XrdSsiCl
{
extern const char *cmdName;

extern       FILE *outFile;
}

using namespace XrdSsiCl;
using namespace std;

/******************************************************************************/
/*                           C o n s t r u c t o r                            */
/******************************************************************************/
  
XrdSsiClUI::XrdSsiClUI()
{
   contact    = 0;
   sessName   = 0;
   timeOut    = 0;
   readSZ     = 1024*1024;
   isAsync    = false;
   doEcho     = true;
   ssiService = 0;
   ssiSession = 0;
   sessList   = 0;
   iSession   = 0;
   reqBuff    = 0;
   reqBpad    = 0;
   srcFD      = 0;
   strcpy(prompt, "> ");

   cLine.Attach(STDIN_FILENO);
}

/******************************************************************************/
/*                            A d d S e s s i o n                             */
/******************************************************************************/
  
void XrdSsiClUI::AddSession(const char *sName, XrdSsiSession *sP)
{
   char *theSess = strdup(sName);

// Lock this code path
//
   uiMutex.Lock();

// Simply get a new session object and chain it in
//
   sessList = new Session(theSess, sP, sessList);

// Activate the session if we have none
//
   if (!ssiSession)
      {sessName = theSess;
       ssiSession = sP;
       snprintf(prompt, sizeof(prompt), "%s> ", sessName);
       cout <<'\n' <<prompt; cout.flush();
      }

// Unlock
//
   uiMutex.UnLock();
}

/******************************************************************************/
/*                            D e l S e s s i o n                             */
/******************************************************************************/
  
void XrdSsiClUI::DelSession(const char *sName)
{
   Session *sP, *pP;

// Lock this code path
//
   uiMutex.Lock();

// Find the session in the list and remove it
//
   if ((sP = FindSession(sName, &pP)))
       {if (!pP) sessList = sP->next;
           else pP->next = sP->next;
        delete sP;
       }

// If this is the current session, make it go away
//
   if (sessName && !strcmp(sName, sessName))
      {sessName   = 0;
       ssiSession = 0;
       strcpy(prompt, "> ");
       cout <<'\n' <<prompt; cout.flush();
      }

// Unlock
//
   uiMutex.UnLock();
}

/******************************************************************************/
/* Private:                       D o S e s s                                 */
/******************************************************************************/
  
bool XrdSsiClUI::DoSess()
{
   Session *sP;
   char    *var;

// Session name
//
   if (!(var = cLine.GetToken()) || !(*var))
      {cerr <<"Session name not specified." <<endl;
       return false;
      }

// Lock this code path
//
   uiMutex.Lock();

// Check if a simple list wanted
//
   if (!strcmp(var, "*"))
      {if (!(sP = sessList)) cerr <<"No sessions found." <<endl;
          else while(sP) {cerr <<sP->sessN <<endl; sP = sP->next;}
       uiMutex.UnLock();
       return false;
      }

// Check if this is a reference to an existing session
//
   if ((sP = FindSession(var)))
      {sessName   = sP->sessN;
       ssiSession = sP->sessP;
       snprintf(prompt, sizeof(prompt), "%s> ", sessName);
       uiMutex.UnLock();
       return false;
      }

// Indicate a new session is to be started
//
   strcpy(reqBuff, var);
   uiMutex.UnLock();
   return true;
}

/******************************************************************************/
/* private:                        D o S e t                                  */
/******************************************************************************/
  
void XrdSsiClUI::DoSet()
{
   static const int maxRsz = 1024*1024;
   char *var;
   long long val;

// Check if a display of values wanted
//
   if (!(var = cLine.GetToken()) || !(*var))
      {cerr <<(doEcho ? "echo" : "noecho") <<" pad " <<reqBpad
            <<" rdsz " <<readSZ <<endl;
       return;
      }

// Check for valid options
//
        if (!strcmp(var, "echo"))   doEcho = true;
  else  if (!strcmp(var, "noecho")) doEcho = false;
  else  if (!strcmp(var, "pad"))
           {if (!(var = GetToken("pad size"))
            ||   (val = GetSize("pad size", var, maxBsz)) < 0) return;
            reqBpad = (val < minBsz ? minBsz : val);
            if (reqBpad != reqBsz)
               {if (reqBuff) free(reqBuff);
                reqBsz = reqBpad;
                reqBuff = (char *)malloc(reqBsz);
               }
           }
  else  if (!strcmp(var, "rdsz"))
           {if (!(var = GetToken("read size"))
            ||   (val = GetSize("read size", var, maxRsz)) < 0) return;
            readSZ = (val ? val : 1);
           }
   else cerr <<"Invalid set argument - " <<var <<endl;
}

/******************************************************************************/
/* Private:                     D o S o u r c e                               */
/******************************************************************************/

void XrdSsiClUI::DoSource()
{
   char *fname;
   int fd;

   if (!(fname = GetToken("file"))) return;

   if ((fd = open(fname, O_RDONLY)) < 0)
      {cerr <<strerror(errno) <<" sourcing " <<fname <<endl; return;}

   if (!srcFD) cLine.Detach();
   srcFD = fd;
   cLine.Attach(fd);
}
  
/******************************************************************************/
/* Private:                  F i n d S e s s i o n                            */
/******************************************************************************/
  
XrdSsiClUI::Session *XrdSsiClUI::FindSession(const char           *sname,
                                             XrdSsiClUI::Session **psP)
{
   Session *pP = 0, *sP = sessList;

// Find the session
//
   while(sP && strcmp(sP->sessN, sname)) {pP = sP; sP = sP->next;}

// Return result
//
   if (psP) *psP = pP;
   return sP;
}

/******************************************************************************/
/* Private:                       G e t N u m                                 */
/******************************************************************************/
  
bool XrdSsiClUI::GetNum(const char *opT, char *opV, int &opD)
{
    char *eP;

    errno = 0;
    opD  = strtol(opV, &eP, 10);
    if (errno || *eP)
       {cerr <<cmdName <<"Invalid " <<opT <<" argument, '" <<opV <<"'." <<endl;
        return false;
       }
    return true;
}

/******************************************************************************/
/* Private:                      G e t S i z e                                */
/******************************************************************************/

long long XrdSsiClUI::GetSize(const char *tName, char *var, long long maxV)
{
    char *eP;
    long long val;

    errno = 0;
    val  = strtol(var, &eP, 10);
     if (!errno && val >= 0)
        {if (*eP)
            {     if (*(eP+1)) val = -1;
                  if (*eP == 'k' || *eP == 'K') val *= 1024LL;
             else if (*eP == 'm' || *eP == 'M') val *= 1024LL*1024LL;
             else val = -1;
            }
        }

    if (val < 0)
       {cerr <<"Invalid " <<tName <<" argument, '" <<var <<"'." <<endl;
        return -1;
       }

    if (maxV >= 0 && val > maxV)
       {cerr <<tName <<" must be <= " <<maxV <<endl;
        return -1;
       }

    return val;
}
  
/******************************************************************************/
/* Private:                     G e t T o k e n                               */
/******************************************************************************/

char *XrdSsiClUI::GetToken(const char *tName)
{
   char *var;

   if (!(var = cLine.GetToken()) || !(*var))
      cerr <<tName <<" not specified." <<endl;

   return var;
}
  
/******************************************************************************/
/*                            G e t R e q u e s t                             */
/******************************************************************************/
  
XrdSsiClUI::Action XrdSsiClUI::GetRequest(int &reqLen)
{
   char *line, *var;

// Get a buffer if we have none
//
   if (!reqBuff) reqBuff = (char *)malloc(reqBsz);

// Check if we start with an initial session
//
   if (iSession)
      {strcpy(reqBuff, iSession);
       iSession = 0;
       return Provision;
      }

// Issue initial prompt
//
   cout <<prompt; cout.flush();

// Get commands
//
do{while(!(line = cLine.GetLine()) || !(*line))
        {if (srcFD) {cLine.Attach(STDIN_FILENO); srcFD = 0;}
         cout <<prompt; cout.flush();
        }
   if (srcFD) {cout <<line <<endl; cout.flush();}

   if (!(var = cLine.GetToken(&line)) || !(*var)) continue;

        if (!strcmp(var, "help"))
           Help();
   else if (!strcmp(var, "cancel"))
           return CancelRequest;
   else if (!strcmp(var, "qloc"))
           {uiMutex.Lock();
            if (!ssiSession) cerr <<"No session is active." <<endl;
               else cerr <<ssiSession->Location() <<endl;
            uiMutex.UnLock();
           }
   else if (!strcmp(var, "reprovision"))
           return Reprovision;
   else if (!strcmp(var, "send"))
           {int n = strlen(line);
            strcpy(reqBuff, line);
            if (n > reqBpad) reqLen = n+1;
               else reqLen = reqBpad;
            return SendRequest;
           }
   else if (!strcmp(var, "session"))
           {if (DoSess()) return Provision;}
   else if (!strcmp(var, "set"))
           DoSet();
   else if (!strcmp(var, "source"))
           DoSource();
   else if (!strcmp(var, "unprovision"))
           return Unprovision;
   else if (!strcmp(var, "stop")) break;
   else if (!strcmp(var, "quit") || !strcmp(var, "exit")) exit(0);
   else cerr <<"Invalid command - " <<var <<endl;
   if (!srcFD) cout <<prompt; cout.flush();
  } while(1);

  return StopService;
}

/******************************************************************************/
/* Private:                         H e l p                                   */
/******************************************************************************/

void XrdSsiClUI::Help()
{
   cerr <<"canel\n"
        <<"     Attempt to cancel current request (risky affair).\n"
        <<"exit\n"
        <<"     Immediately exit the program (quit is a synonym).\n"
        <<"qloc\n"
        <<"     Display the session's endpoint.\n"
        <<"reprovision\n"
        <<"     Reprovision the current session.\n"
        <<"send <request_data>\n"
        <<"     Send a request to the current session endpoint:\n"
        <<"          delay <sec>\n"
        <<"          echo  <data>\n"
        <<"          error <enum> <etext>\n"
        <<"          file  <path>\n"
        <<"          resume\n"
        <<"          stream [active | passive | <rdsz> | <path>]\n"
        <<"          suspend\n"
        <<"session {* | <sessname>}\n"
        <<"     List active sessions or switch to one (provision if new).\n"
        <<"set [pad <sz>] [rdsz <sz>] [echo] [noecho]\n"
        <<"     List settings or set a value:\n"
        <<"          pad    - sets request padding size.\n"
        <<"          rdsz   - sets response read size.\n"
        <<"source <file>\n"
        <<"     Get subsequent commands from <file> until eof.\n"
        <<"stop\n"
        <<"     Stop the service and exit upon success.\n"
        <<"unprovision\n"
        <<"     Unprovision the current session.\n"
        <<endl;
}
  
/******************************************************************************/
/*                               P a r s e C L                                */
/******************************************************************************/
  
bool XrdSsiClUI::ParseCL(int argc, char **argv)
{
   extern char *optarg;
   extern int optind, opterr;
   char *fifoFN = 0, *Slash, buff[512], c;
   bool asyncOut = false;

// Get the command name
//
   if ((Slash = rindex(argv[0], '/'))) Slash = Slash+1;
      else Slash = argv[0];
   sprintf(buff, "%s: ", Slash);
   cmdName = strdup(buff);

// Process the options.
//
   opterr = 0;
   if (argc > 1 && '-' == *argv[1]) 
      while ((c = getopt(argc,argv,":at:o:"))
             && ((unsigned char)c != 0xff))
     { switch(c)
       {
       case 'a': asyncOut = true;
                 break;
       case 'o': fifoFN = optarg;
                 break;
       case 't': if (!GetNum("-t", optarg, timeOut)) return false;
                 break;
       case ':': buff[0] = '-'; buff[1] = optopt; buff[2] = 0;
                 cerr <<cmdName <<buff <<"parameter not specified." <<endl;
                 return Usage();
                 break;

       default:  break;
       }
     }

// Get the parameters
//
   if (optind >= argc)
      {cerr <<cmdName <<"Contact point not specified." <<endl;
       return Usage();
      }
   contact = argv[optind];

// Get initial session
//
   if (optind+1 < argc) iSession = argv[optind+1];

// See if we are going to output to a fifo or inline
//
   if (asyncOut)
      {const char *theFN = (fifoFN ? fifoFN : "/tmp/ssiclfifo");
       if (mkfifo(theFN, 0700) && errno != EEXIST)
          {cerr <<cmdName <<"Unable to create fifo " <<theFN <<"; "
                <<strerror(errno) <<endl;
           return false;
          }
       if (!(outFile = fopen(theFN, "w")))
          {cerr <<cmdName <<"Unable to open fifo " <<theFN <<"; "
                <<strerror(errno) <<endl;
           return false;
          }
      }

// All done
//
   return true;
}

/******************************************************************************/
/*                                 U s a g e                                  */
/******************************************************************************/
  
bool XrdSsiClUI::Usage()
{
   cerr <<"Usage: ssicl <host>:<port> [session]" <<endl;
   cerr <<"       opts: [-a] [-o <outfifo>] [-t <sec>]" <<endl;
   return false;
}
