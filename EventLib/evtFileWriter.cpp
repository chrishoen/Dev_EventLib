/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risFileFunctions.h"

#include "evtFileWriter.h"

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

FileWriter::FileWriter()
{
   mLogFilePath = "C:\\aaa_prime\\EventLib\\np_tta_eventlog.txt";
   mAlarmFilePath = "C:\\aaa_prime\\EventLib\\np_tta_alarmlist.txt";
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write an event table record as a json string to the event log file.

void FileWriter::doWriteToLogFile(
   EventTableRecord& aEventTableRecord)     // Input
{
   // Get json string formatted for a log file.
   std::string tString = aEventTableRecord.getLogFileJsonString();

   // Write append the string to the log file.
   doAppendStringToFile(tString, &mLogFilePath[0]);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write an event table record as a json string to the alarm list file.

void FileWriter::doWriteToAlarmFile(
   EventTable& aEventTable,       // Input
   AlarmList&  aAlarmList)        // Input   
{
   // Open the output file for write.
   std::ofstream tOutputFile(mAlarmFilePath, std::ofstream::out);

   // Loop for all of the event ids in the alarm list event id set.
   for (AlarmList::IntSetItr tItr = aAlarmList.mEvtIdSet.begin(); tItr != aAlarmList.mEvtIdSet.end(); ++tItr)
   {
      // Get json string formatted for an alarm file.
      std::string tString = aEventTable.mArray[*tItr].getLogFileJsonString();
      // Write the string to the alarm file.
      tOutputFile << tString;
   }

   // Done
   tOutputFile.close();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write append a string to a file.

void FileWriter::doAppendStringToFile(
   const std::string& aString,        // Input
   const std::string& aFilePath)      // Input
{
   std::ofstream tOutputFile(aFilePath, std::ofstream::app);
   tOutputFile << aString;
   tOutputFile.close();
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace