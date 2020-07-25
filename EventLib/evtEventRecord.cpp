/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include <stdarg.h>
#include <ctype.h>

#include "evtEventThread.h"
#include "evtEventRecord.h"

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

EventRecord::EventRecord()
{
   reset();
}

EventRecord::EventRecord(int aEvtId)
{
   reset();
   mEvtId = aEvtId;
}
EventRecord::EventRecord(int aEvtId, bool aCState)
{
   reset();
   mEvtId = aEvtId;
   mCState = aCState;
}
EventRecord::EventRecord(int aEvtId, bool aCState, int aSeverity)
{
   reset();
   mEvtId = aEvtId;
   mCState = aCState;
   mSeverity = aSeverity;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void EventRecord::reset()
{
   mEvtId = 0;
   timespec_get(&mTOA, TIME_UTC);
   mSeverity = cEvt_SevUseDefault;
   mCState = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set the argumant strings via a variable arg list using vnsprintf.

void EventRecord::setArg1(const char* aFormat, ...)
{
   // Do a vsprintf with variable arg list into the argument string.
   int tPrintSize = 0;
   va_list  ArgPtr;
   va_start(ArgPtr, aFormat);
   tPrintSize = vsnprintf(mArgString1, cMaxRecordArgSize - 1, aFormat, ArgPtr);
   va_end(ArgPtr);
   mArgString1[tPrintSize++] = 0;
}

void EventRecord::setArg2(const char* aFormat, ...)
{
   // Do a vsprintf with variable arg list into the argument string.
   int tPrintSize = 0;
   va_list  ArgPtr;
   va_start(ArgPtr, aFormat);
   tPrintSize = vsnprintf(mArgString2, cMaxRecordArgSize - 1, aFormat, ArgPtr);
   va_end(ArgPtr);
   mArgString1[tPrintSize++] = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void EventRecord::show(int aPF)
{
   char tBuffer[40];
   Prn::print(aPF, "EventRecord********************************");
   Prn::print(aPF, "EvtId                   %-5d",    mEvtId);

   Prn::print(aPF, "TOA                     %s",      get_timespec_asString(mTOA,tBuffer));
   Prn::print(aPF, "Severity                %-s",     get_EvtSeverity_asString(mSeverity));
   Prn::print(aPF, "CState                  %-s",     my_string_from_bool(mCState));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Send this instance to the event thread. The event thread will
// eventually delete this instance. Do not use this instance after
// sending it. If this is not successful then it deletes itself.

void EventRecord::sendToEventThread()
{
   // Guard.
   if (gEventThread == 0)
   {
      delete this;
      return;
   }

   // Send this instance to the event thread.
   if (!gEventThread->tryWriteEventRecord(this))
   {
      delete this;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace