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
   // Guard.
   if (aEventTableRecord->mType == cEvt_Type1) return false;
   
   // If the cstate is true then add the event id to the set.
   if (aEventTableRecord->mCState)
   { 
      mEvtIdSet.insert(aEventTableRecord->mEvtId);
   }
   // If the cstate is false then remove the event id from the set.
   else
   {
      mEvtIdSet.erase(aEventTableRecord->mEvtId);
   }

   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void AlarmList::show(int aPF)
{
   Prn::print(aPF, "AlarmList***************************************");
   for (IntSetItr tItr = mEvtIdSet.begin(); tItr != mEvtIdSet.end(); ++tItr)
   {
      Prn::print(aPF, "%d", *tItr);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace