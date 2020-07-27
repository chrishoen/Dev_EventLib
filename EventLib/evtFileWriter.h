#pragma once

/*==============================================================================
File writer for event log files and alarm list file.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "evtEventDefs.h"
#include "evtEventTableRecord.h"

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a class that implments a file writer for event table records.
// Table records are formatted into json strings and the strings are written
// to either the event log file or the alarm list file.

class FileWriter
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   static const int cMaxStringSize = 200;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // File paths for the event log and the alarm list files.
   char mLogFilePath[cMaxStringSize];
   char mAlarmFilePath[cMaxStringSize];

   // Constructor.
   FileWriter();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Write an event table record as a json string to the event log file.
   void doWriteJsonToLogFile(EventTableRecord* aEventTableRecord);

   // Write an event table record as a json string to the alarm list file.
   void doWriteJsonToAlarmFile(EventTableRecord* aEventTableRecord);

   // Write append a string to a file.
   void doAppendStringToFile(
      const std::string& aString,        // Input
      const std::string& aFilePath);     // Input
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


