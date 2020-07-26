#pragma once

/*==============================================================================
Provides a class definition for the active alarm list
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <set> 
#include <iterator> 

#include "evtEventDefs.h"
#include "evtEventTableRecord.h"

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a class that implments an active alarm list, which is a std::set of
// integers that contain the event ids for type2 events that have cstate true.

class AlarmList
{
public:
   typedef std::set<int, std::less<int>> IntSet;
   typedef std::set<int, std::less<int>>::iterator IntSetItr;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // This is a set of integers that contain event ids of type2 events in
   // the event table that have cstate true.
   IntSet mEvtIdSet;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   AlarmList();
   void reset();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Update the integer set table with an event table record. Return true if
   // the table was updated. Retun false if it was not. If this is for a
   //  type1 event then then the set is not changed. If this is for a type2
   // event and the cstate is true then the event id for the record is inserted
   // into the set. If it is false, then it is removed from the set.
   bool update(EventTableRecord* aEventTableRecord);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Show.
   void show(int aPrintFilter);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


