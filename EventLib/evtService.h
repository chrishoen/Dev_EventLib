#pragma once

/*==============================================================================
Provides an interface to the event processing service.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "evtEventDefs.h"
#include "evtEventRecord.h"

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Functions.

   // Check the function parameters to determine if they will actually
   // change the event table. If they will not and if an event is not
   // currently pending then don't send the event. If they will change the
   // event table or if there is already an event pending then send the
   // event. This involves some gnarly concurrency logic that uses an
   // atomic int.
   void doSendEvent(int aEvtId, bool aCState = true, int aSeverity = 0);

   // Check the function parameters to determine if they will actually
   // change the event table. If they will not and if an event is not
   // currently pending then return a null pointer. If they will change
   //  the event table or if there is already an event pending then
   // create a new event record and return it. This involves some gnarly
   // concurrency logic that uses an atomic int.
   EventRecord* trySendEvent(int aEvtId, bool aCState = true, int aSeverity = 0);

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


