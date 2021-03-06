#pragma once

/*==============================================================================
Provides a class definition of event table records.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <time.h>
#include <atomic>
#include "json.h"

#include "evtEventDefs.h"
#include "evtEventRecord.h"

namespace Evt
{

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
   // Members, permanent. These are assigned at initialization.

   // Event identifier.
   int mEvtId;

   // Event type.
   int mType;

   // Default severity.
   int mDefaultSeverity;

   // Show string for set.
   const char* mShowStringForSet;

   // Show string for clear.
   const char* mShowStringForClear;

   // Show string for the active alarm list.
   const char* mShowStringForAlarm;

   // If true then the event associated with this record can be ignored
   // if the severity and cstate are the same.
   bool mIgnoreFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members, transient. These are set according to the occurrence of
   // individual events.

   // Time of arrival.
   timespec mTOA;

   // Variable severity. This is usually equal to the default.
   int mSeverity;

   // True if a type2 event was set. False if cleared. This is only used
   // by type2 events. This is used to define active alarms.
   bool mCState;

   // Two arguments that can be passed to and event. An example: The 
   // temperature went above threshold, arg1 is the temperature and
   // arg2 is the threshold.
   char mArgString1[cMaxRecordArgSize];
   char mArgString2[cMaxRecordArgSize];

   // This is used to track if an event has a message pending in the 
   // event thread pointer que. If it is zero then there are none 
   // pending.
   std::atomic<int> mPendingCount;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   EventTableRecord();
   void reset();

   // Initialize.
   void initialize(
      int aEvtId,
      int aType,
      int aDefaultSeverity,
      const char* aShowStringForSet,
      const char* aShowStringForClear,
      const char* aShowStringForAlarm);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Update with an event record. Return true if the record was updated. 
   // Return false if it was not. If this is for a type1 event then
   // it is updated. If this is for a type2 event and the cstate or severity
   // changed then it is updated.
   bool update(EventRecord* aEventRecord);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Show.
   void show(int aPrintFilter = 0);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // return a string that represents the cstate.
   const char* getCStateAsString();

   // Write a show string into a buffer string. return a pointer to the buffer.
   char* getLogFileShowString(char* aBuffer);
   char* getAlarmFileShowString(char* aBuffer);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Return a string for all of the variables.
   std::string getLogFileJsonString();

   // Return a string for all of the variables.
   std::string getAlarmFileJsonString();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Return true if these variables will change the record.
   bool willChange(int aSeverity, bool aCState);
};



//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


