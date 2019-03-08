#ifndef __XRDSSISVSTREAMPASSIVE_HH__
#define __XRDSSISVSTREAMPASSIVE_HH__
/******************************************************************************/
/*                                                                            */
/*              X r d S s i S v S t r e a m P a s s i v e . h h               */
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

#include "XrdSsi/XrdSsiStream.hh"

// This class displays how to use passive streams. Streams are good for
// streaming data out of a data source that can't give you the full response
// or one whose response exceeds a normal "read" size. This class implements a
// passive stream (i.e. fills a supplied data buffer).
//
class XrdSsiSvStreamPassive : public XrdSsiStream
{
// The following method simply attaches a file to the stream
//
int     Attach(const char *fname);

// This is called for passive streams
//
        int     SetBuff(XrdSsiErrInfo &eInfo, char *buff, int  blen,
                        bool async=false);

                XrdSsiSvStreamPassive() : XrdSsiStream(isPassive) {}

               ~XrdSsiStreamPassive() {}

private:
};
#endif
