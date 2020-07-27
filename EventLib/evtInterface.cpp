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
// Check the function parameters to determine if they will actually
// change the event table. If they will not and if an event is not
// currently pending.

void doSendEvent(int aEvtId)
{
   // Create a new event record.
   int tEvtId = aEvtId;
   int tSeverity = cEvt_SevUseDefault;
   bool tCState = true;
   Evt::EventRecord* tEventRecord = new Evt::EventRecord(tEvtId, tSeverity, tCState);

   // Send it to the event thread.
   tEventRecord->sendToEventThread();
}

void doSendEvent(int aEvtId, bool aCState)
{
   // Create a new event record.
   int tEvtId = aEvtId;
   int tSeverity = cEvt_SevUseDefault;
   bool tCState = aCState;
   Evt::EventRecord* tEventRecord = new Evt::EventRecord(tEvtId, tSeverity, tCState);

   // Send it to the event thread.
   tEventRecord->sendToEventThread();
}

void doSendEvent(int aEvtId, int aSeverity, bool aCState)
{
   // Create a new event record.
   int tEvtId = aEvtId;
   int tSeverity = aSeverity;
   bool tCState = aCState;
   Evt::EventRecord* tEventRecord = new Evt::EventRecord(tEvtId, tSeverity, tCState);

   // Send it to the event thread.
   tEventRecord->sendToEventThread();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace