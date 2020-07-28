/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "evtEventStore.h"

#define  _EVENTTHREAD_CPP_
#include "evtEventThread.h"

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

EventThread::EventThread()
{
   // Set base class thread variables.
   BaseClass::setThreadName("EventThread");
   BaseClass::setThreadPrintLevel(TS::PrintLevel(0, 3));
   BaseClass::setThreadPriorityNormal();
   mTerminateFlag = false;
}

EventThread::~EventThread()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immediately 
// after the thread starts running. This opens the file.

void EventThread::threadInitFunction()
{
   Prn::print(Prn::View11, "EventThread::threadInitFunction**********************");
   printf("LINE101\n");
   // Initialize the string queue.
   mEventRecordQueue.initialize(cQueueSize);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function, base class overload. This closes the file.

void  EventThread::threadExitFunction()
{
   Prn::print(Prn::View11, "EventThread::threadExitFunction**********************");

   // Finalize the string queue.
   mEventRecordQueue.finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread run function. This is called by the base class immediately 
// after the thread init function. It runs a loop that waits on the
// semaphore. When it wakes up, it reads a string from the string
// queue and prints it.

void EventThread::threadRunFunction()
{
   // Loop to wait for posted events and process them.
   int tCount = 0;
   while (true)
   {
      // Wait on the counting semaphore.
      mSemaphore.get();

      // Test for thread termination.
      if (mTerminateFlag) break;

      // Try to read a string from the queue.
      if (EventRecord* tEventRecord = (EventRecord*)mEventRecordQueue.tryRead())
      {
         // Print the string to the log file and then delete it.
         processEventRecord(tEventRecord);
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread shutdown function. Set the termination flag, post to the 
// semaphore and wait for the thread to terminate.

void EventThread::shutdownThread()
{
   shutdownThreadPrologue();

   // Set the termination flag.
   mTerminateFlag = true;
   // Post to the semaphore.
   mSemaphore.put();
   // Wait for the thread run function to return.
   BaseClass::waitForThreadTerminate();
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Event record request qcall. Update the event table and the alarm list.
// Update the event log file and the alarm list file. Delete the event
// record when finiished.

void EventThread::processEventRecord(EventRecord* aEventRecord)
{
   Prn::print(Prn::View11, "processEventRecord %d", aEventRecord->mEvtId);

   // Update the event table with the event record.
   if (Evt::gEventStore.mEventTable.update(aEventRecord))
   {
      // If the table was changed:
      char tBuffer[200];
      int tEvtId = aEventRecord->mEvtId;

      // Print.
      Prn::print(Prn::View11, "%s",
         gEventStore.mEventTable.mArray[tEvtId].getLogFileShowString(tBuffer));

      // Write to the event log file.
      gEventStore.mFileWriter.doWriteToLogFile(
         gEventStore.mEventTable.mArray[tEvtId]);

      // Update the alarm list.
      if (Evt::gEventStore.mAlarmList.update(
         &Evt::gEventStore.mEventTable.mArray[tEvtId]))
      {
         // Write to the alarm list file.
         gEventStore.mFileWriter.doWriteToAlarmFile(
            gEventStore.mEventTable,
            gEventStore.mAlarmList);
      }
   }

   // Done.
   delete aEventRecord;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Try to write an event record to the to the queue. Return true if
// successful. This is called by invocations to enqueue an event record.
// It writes to the pointer queue and posts to the semaphore, which
// then wakes up the thread run function to process the queue.

bool EventThread::tryWriteEventRecord(EventRecord* aEventRecord)
{
   // Guard.
   if (mTerminateFlag) return false;

   // Try to write to the call queue.
   if (!mEventRecordQueue.tryWrite(aEventRecord))
   {
      // The write was not successful.
      return false;
   }

   // Post to the semaphore.
   mSemaphore.put();

   // Successful.
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace