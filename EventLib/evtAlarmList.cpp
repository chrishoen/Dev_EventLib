/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "evtAlarmList.h"

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

AlarmList::AlarmList()
{
   reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void AlarmList::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Update the table with an event record. Return true if the table was
// updated. Return false if it was not. If this is for a type1 event then
// it is updated. If this is for a type2 event and the cstate or severity
// changed then it is updated.

bool AlarmList::update(EventTableRecord* aEventTableRecord)
{
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void AlarmList::show()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace