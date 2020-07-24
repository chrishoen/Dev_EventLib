#pragma once

/*==============================================================================
Provides a class definition of event records.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <time.h>
#include "evtEventDefs.h"

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a class that implments a record for occurrences of events. 
// It contains variables that define the properties of an event.
// Instances are used to update the event table. 
class EventRecord
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Event identifier.
   int mEvtId;

   // Time of arrival.
   timespec mTOA;

   // Sequence number. This is incremented for each individual event that
   // occurs.
   int mSeqNum;

   // Variable severity. This is usually equal to the default.
   int mSeverity;

   // True if a type2 event was set. False if cleared. This is only used
   // by type2 events. This is used to define active alarms.
   bool mCState;

   // Two arguments that can be passed to an event. An example: The 
   // temperature went above threshold, arg1 is the temperature.
   char mArgString1[cMaxRecordArgSize];
   char mArgString2[cMaxRecordArgSize];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   EventRecord();
   void reset();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Show.
   void show(int aPrintFilter = 0);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


