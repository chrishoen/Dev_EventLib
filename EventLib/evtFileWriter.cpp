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
   strcpy(mLogFilePath, "C:\\aaa_prime\\EventLib\np_tta_eventlog.txt");
   strcpy(mAlarmFilePath, "C:\\aaa_prime\\EventLib\np_tta_alarmlist.txt");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write an event table record as a json string to the event log file.

void FileWriter::doWriteJsonToLogFile(EventTableRecord* aEventTableRecord)
{
   // Get json string formatted for a log file.
   std::string tString = aEventTableRecord->getLogFileJsonString();

   // Write append the string to the log file.
   doAppendStringToFile(tString, mLogFilePath);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write an event table record as a json string to the alarm list file.

void FileWriter::doWriteJsonToAlarmFile(EventTableRecord* aEventTableRecord)
{
   // Get json string formatted for an alarm file.
   std::string tString = aEventTableRecord->getLogFileJsonString();

   // Write append the string to the alarm file.
   doAppendStringToFile(tString, mAlarmFilePath);
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