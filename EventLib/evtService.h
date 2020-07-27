#pragma once

/*==============================================================================
Provides an interface to the event processing service.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "evtEventDefs.h"

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Functions.

   // Check the function parameters to determine if they will actually
   // change the event table. If they will not and if an event is not
   // currently pending.
   void doSendEvent(int sEvtId);
   void doSendEvent(int sEvtId, bool aCState);
   void doSendEvent(int sEvtId, int aSeverity, bool aCState);

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

