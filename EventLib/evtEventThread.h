#pragma once

/*==============================================================================
Event processing thread
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>

#include "risThreadsThreads.h"
#include "risThreadsSynch.h"
#include "risLCPointerQueue.h"

#include "evtEventRecord.h"

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This thread provides serialized access to the event table and the
// alarm list. It provides a method that sends an event record to the thread.
// It processes the event record to update the event table and alarm list and
// then update the event log file and the alarm list file.
//   
// It contains a pointer queue and a counting semaphore. Threads that use
// this thread as a service to process ana event record write an event record
// pointer to the queue and post to the semaphore. This thread waits on the
// semaphore and, when it wakes up, reads an event record from the queue and
// processes it.

// It inherits from BaseThread to obtain thread functionality.
// 

class EventThread : public Ris::Threads::BaseThread
{
public:
   typedef Ris::Threads::BaseThread BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   static const int cMaxStringSize = 400;
   static const int cQueueSize = 1000;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Pointer queue that contains pointers to strings. Print invocations
   // enqueue strings to this queue. This thread dequeues strings from it and
   // prints them to the stdout and the program log file.
   Ris::LCPointerQueue mEventRecordQueue;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Counting semaphore. The thread run function contains a loop that
   // waits on this for a timer or an event. The timer provides for
   // periodic exectution and the event can signify that the call queue is
   // ready or it can signify for thread termination.
   Ris::Threads::CountingSemaphore mSemaphore;

   // If true the the thread will terminate at the next post to the
   // semaphore.
   bool mTerminateFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   EventThread();
  ~EventThread();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Thread base class overloads.

   // Thread init function. This is called by the base class immediately 
   // after the thread starts running.
   void threadInitFunction() override;

   // Thread run function. This is called by the base class immediately 
   // after the thread init function. It runs a loop that waits on the
   // semaphore. When it wakes up, it reads an event record from the 
   // queue and processes it.
   void threadRunFunction() override;

   // Thread exit function. This is called by the base class immediately
   // before the thread is terminated.
   void threadExitFunction() override;

   // Thread shutdown function. Set the termination flag, post to the 
   // semaphore and wait for the thread to terminate.
   void shutdownThread() override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Process an event record. Update the event table and the alarm list.
   // Update the event log file and the alarm list file. Delete the event
   // record when finiished.
   void processEventRecord (EventRecord* aString);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Try to write an event record to the to the queue. Return true if
   // successful. This is called by invocations to enqueue an event record.
   // It writes to the pointer queue and posts to the semaphore, which
   // then wakes up the thread run function to process the queue.
   bool tryWriteEventRecord(EventRecord* aString);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global singular instance.

#ifdef _EVENTTHREAD_CPP_
         EventThread* gEventThread = 0;
#else
extern   EventThread* gEventThread;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
