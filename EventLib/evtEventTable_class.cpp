/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "evtEventTable.h"

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

EventTable::EventTable()
{
   reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void EventTable::reset()
{
   for (int i = 0; i < cEvt_MaxNumEvents; i++)
   {
      mArray[i].reset();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Update the table with an event record. Return true if the table was
// updated. Return false if it was not. If this is for a type1 event then
// it is updated. If this is for a type2 event and the cstate or severity
// changed then it is updated.

bool EventTable::update(EventRecord* aEventRecord)
{
   // Nickname.
   EventTableRecord* tTableRecord = &mArray[aEventRecord->mEvtId];

   // Make the input event record consistent.
   if (aEventRecord->mCState && aEventRecord->mSeverity == cEvt_SevUseDefault)
   {
      // Overwrite the input event record severity with the table record
      // default.
      aEventRecord->mSeverity = tTableRecord->mDefaultSeverity;
   }
   // Test if the table record needs to be updated.
   bool tChangeFlag = false;

   // For type1, always update.
   if (tTableRecord->mType == cEvt_Type1) tChangeFlag = true;

   // For type2, test some variables. If they don't change, then don't 
   // update.
   if (tTableRecord->mType == cEvt_Type2)
   {
      // Test for a change in variables.
      if (tTableRecord->mCState   != aEventRecord->mCState) tChangeFlag = true;

      if (tTableRecord->mCState)
      {
         if (tTableRecord->mSeverity != aEventRecord->mSeverity) tChangeFlag = true;
      }
   }
   Prn::print(Prn::View11, "LINE101 %d", tChangeFlag);
   // If no change then done.
   if (!tChangeFlag) return false;

   // If it doesn't then update the table record
   tTableRecord->update(aEventRecord);
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void EventTable::showRecord(int aEvtId, int aPF)
{
   mArray[aEvtId].show(aPF);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace