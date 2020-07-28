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
#include "evtEventStore.h"

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Check the function parameters to determine if they will actually
// change the event table. If they will not and if an event is not
// currently pending.

void doSendEvent(int aEvtId, bool aCState, int aSeverity)
{
   // Increment the pending count.
   gEventStore.mEventTable.mArray[aEvtId].mPendingCount++;

   // Test if the event should be sent.
   bool tSendFlag = false;
   // Always send type2 events
   if (gEventStore.mEventTable.mArray[aEvtId].mType == cEvt_Type1)
   {
      tSendFlag = true;
   }
   // Test type2 events.
   else
   {
      // If an event is aalready pending in the message queue then send it
      if (gEventStore.mEventTable.mArray[aEvtId].mPendingCount.load() != 1) tSendFlag = true;
      // If the event table will change then send it.
      if (gEventStore.mEventTable.mArray[aEvtId].willChange(aSeverity, aCState)) tSendFlag = true;
   }

   // Send the event to the event thread.
   if (tSendFlag)
   {
      // Create a new event record.
      int tEvtId = aEvtId;
      bool tCState = aCState;
      int tSeverity = aSeverity;
      Evt::EventRecord* tEventRecord = new Evt::EventRecord(tEvtId, tCState, tSeverity);

      // Send it to the event thread.
      tEventRecord->sendToEventThread();
   }
   // Don't send the event to the event thread.
   else
   {
      // Increment the pending count.
      gEventStore.mEventTable.mArray[aEvtId].mPendingCount++;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace