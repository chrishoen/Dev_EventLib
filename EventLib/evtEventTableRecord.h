#pragma once

/*==============================================================================
Provides a class definition of event table records.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <time.h>
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

   // Update with an event record.
   void update(EventRecord* aEventRecord);

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
   char* getShowString(char* aBuffer);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Return a json value for all of the variables.
   Json::Value getLogFileJsonValue();

   // Return a string with json for all of the variables.
   std::string getLogFileJsonString();
};



//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


