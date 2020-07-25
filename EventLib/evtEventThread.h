#pragma once

/*==============================================================================
Event processing thread
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************


#include "risThreadsQCallThread.h"
#include "evtEventRecord.h"

namespace Evt
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This qcall thread provides serialized access to the event table and the
// alarm list. It provides a qcall that sends an event record to the thread.
// It processes the event record to update the event table and alarm list and
// then update the event log file and the alarm list file.

class  EventThread : public Ris::Threads::BaseQCallThread
{
public:
   typedef Ris::Threads::BaseQCallThread BaseClass;

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

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Thread init function. This is called by the base class immediately 
   // after the thread starts running.
   void threadInitFunction() override;

   // Thread exit function. This is called by the base class immediately
   // before the thread is terminated.
   void threadExitFunction() override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Event record request qcall. Update the event table and the alarm list.
   // Update the event log file and the alarm list file. Delete the event
   // record when finiished.
   Ris::Threads::QCall1<EventRecord*> mProcessEventRecordQCall;

   // This is bound to the qcall.
   void executeProcessEventRecord (EventRecord* aEventRecord);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance

#ifdef _EVENTTHREAD_CPP_
          EventThread* gEventThread;
#else
   extern EventThread* gEventThread;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

