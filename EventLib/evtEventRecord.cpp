/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

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
   memset(&mTOA, 0, sizeof(mTOA));
   mSeqNum = 0;
   mSeverity = cEvt_SevUseDefault;
   mCState = false;
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
   Prn::print(aPF, "SeqNum                  %-5d",    mSeqNum);
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
   gEventThread->mProcessEventRecordQCall(this);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace