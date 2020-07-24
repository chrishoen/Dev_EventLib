/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "cmnPriorities.h"
#include "risAlphaDir.h"

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
   BaseClass::setThreadName("EventLog");
   BaseClass::setThreadPriority(Cmn::gPriorities.mEventThread);
   BaseClass::setThreadPrintLevel(TS::PrintLevel(0, 3));

   // Initialize variables.
   mFile = 0;
   mWriteCount = 0;
   mTerminateFlag = false;
}

EventThread::~EventThread()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void EventThread::doFileOpenNew()
{
   // Open the log file.
   mFile = fopen("c:/aaa_prime/EventLib/EventLog.txt", "w");

   if (mFile == 0)
   {
      TS::print(0, "EventLogNew open FAIL");
   }
}

void EventThread::doFileOpenAppend()
{
   // Open the log file.
   mFile = fopen("c:/aaa_prime/EventLib/EventLog.txt", "a+");

   if (mFile == 0)
   {
      TS::print(0, "EventLogAppend open FAIL");
   }
}

void EventThread::doFileClose()
{
   if (mFile)
   {
      fclose(mFile);
      mFile = 0;
   }
}

void EventThread::doFileFlush()
{
   fflush(mFile);
}

void EventThread::doFileWriteTimeStamp()
{
   TString* tString = new TString("PROGRAM START/////////////////////////////////////////////////////////////");
//   tString->sendToEventLog();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immediately 
// after the thread starts running. This opens the file.

void EventThread::threadInitFunction()
{
   Prn::print(Prn::View11, "EventThread*****************************************BEGIN");
   // Initialize the string queue.
   mStringQueue.initialize(cQueueSize);

   // Open the log file.
   doFileOpenAppend();

   // Write a time stamp for the file open.
   doFileWriteTimeStamp();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function, base class overload. This closes the file.

void  EventThread::threadExitFunction()
{
   // Finalize the string queue.
   mStringQueue.finalize();

   // Close the log file.
   doFileClose();

   Prn::print(Prn::View11, "EventThread*****************************************END");
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
      if (TString* tString = (TString*)mStringQueue.tryRead())
      {
         // Print the string to the log file and then delete it.
         printString(tString);
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
// Print a string to stdout and the program log file and delete it.
// log file and then deletes it. This is called by the thread run function
// when it dequeues a string from the queue.

void EventThread::printString(TString* aString)
{
   // Local strings.
   char tTemp[40];
   char tLogString[cMaxStringSize];

   // Copy the input timestamp to the log string.
   strcpy(tLogString, aString->getTime(tTemp));

   // Copy a prefix to the log string.

   switch (aString->mLogCode)
   {
   case cLogAsAny:     strcat(tLogString, " $$$$$  "); break;
   case cLogAsInput:   strcat(tLogString, " <<<    "); break;
   case cLogAsNak:     strcat(tLogString, " nak    "); break;
   case cLogAsOutput:  strcat(tLogString, " >>>>>  "); break;
   case cLogAsSlice:   strcat(tLogString, " SLICE  "); break;
   case cLogAsPWM:     strcat(tLogString, " PWM    "); break;
   case cLogAsTest:    strcat(tLogString, " TEST   "); break;
   case cLogAsCMarker: strcat(tLogString, " MARKER "); break;
   case cLogAsInfo:    strcat(tLogString, " INFO   "); break;
   case cLogAsError:   strcat(tLogString, " ERROR  "); break;
   }

   // Copy the input string to the log string.
   strncat(tLogString, &aString->mString[0], cMaxStringSize);

   // Copy a postfix to the log string.
   strncat(tLogString, "\n", cMaxStringSize);

   // Write the log string to the log file.
   fputs(tLogString, mFile);

   // Metrics.
   mWriteCount++;

   // Done.
   delete aString;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Try to write a string to the to the queue. Return true if
// successful. This is called by print invocations to enqueue a string.
// It writes to the string queue and posts to the semaphore, which
// then wakes up the thread run function to process the string queue.

bool EventThread::tryWriteString(TString* aString)
{
   // Guard.
   if (mTerminateFlag) return false;

   // Try to write to the call queue.
   if (!mStringQueue.tryWrite(aString))
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