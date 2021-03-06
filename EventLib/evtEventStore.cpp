/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#define _EVENTSTORE_CPP_
#include "evtEventStore.h"

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

EventStore::EventStore()
{
   reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void EventStore::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void EventStore::initialize()
{
   mEventTable.initialize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace