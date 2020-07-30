/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risFileFunctions.h"

#include "smShare.h"
#include "evtFileWriter.h"

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

FileWriter::FileWriter()
{
   //mLogFilePath = "C:\\aaa_prime\\EventLib\\np_tta_eventlog.txt";
   //mAlarmFilePath = "C:\\aaa_prime\\EventLib\\np_tta_alarmlist.txt";

   mLogFilePath = "/var/log/np_tta_event.log";
   mAlarmFilePath = "/var/log/np_tta_alarm.txt";
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write an event table record as a json string to the event log file and
// the shared memory event notify queue.

void FileWriter::doWriteToLogFile(
   EventTableRecord& aEventTableRecord)     // Input
{
   Prn::print(Prn::View11, "doWriteToLogFile");

   // Get json string formatted for a log file.
   std::string tString = aEventTableRecord.getLogFileJsonString();

   // Write append the string to the log file.
   doAppendStringToFile(tString, &mLogFilePath[0]);

   // Try to write to the shared memory event notify string.
   if (char* tQueueString = (char*)SM::gShare->mEventNotifyQueue.tryStartWrite())
   {
      Prn::print(Prn::View11, "EVENT NOTIFY QUEUE WRITE");
      // Write the string.
      strncpy(tQueueString, tString.c_str(), SM::gShare->mEventNotifyQueue.cMaxStringSize);
      // Finish the write.
      SM::gShare->mEventNotifyQueue.finishWrite();
   }
   else
   {
      Prn::print(Prn::View11, "EVENT NOTIFY QUEUE FULL");
   }
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
      std::string tString = aEventTable.mArray[*tItr].getAlarmFileJsonString();
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