#pragma once

/*==============================================================================
Provides a class definition of event table records.
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

#include <time.h>
#include "evtEventDefs.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a class that implments a record for enties in the event table. It
// provides storage for event properties and strings. Some of the properties
// are transient, like time of arrival, and apply to occurrences of individual
// events. Some of the properties are permanent, like constant display string
// definitions.

class EventTableRecord
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Permenant Members. These are assigned at initialization.

   // Event identifier.
   int mEvtId;

   // Event type.
   int mType;

   // Default severity.
   int mDefaultSeverity;

   // Show string for set.
   char* mShowStringForSet;

   // Show string for clear.
   char* mShowStringForClear;

   // Show string for the active alarm list.
   char* mShowStringForAlarm;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Transient Members. These are set according to the occurrence of
   // individual events.

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

   // Time difference for a type2 event between the toa of a set and
   // the toa of a clear.
   double mDuration;

   // Two arguments that can be passed to and event. An example: The 
   // temperature went above threshold, arg1 is the temperature.
   char mArgString1[cMaxRecordArgSize];
   char mArgString2[cMaxRecordArgSize];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   EventTableRecord();
   void reset();

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


