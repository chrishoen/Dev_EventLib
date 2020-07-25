/*==============================================================================
File: someTest1Thread.cpp
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"


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
   BaseClass::setThreadPriorityHigh();

   // Set qcalls.
   mProcessEventRecordQCall.bind(this, &EventThread::executeProcessEventRecord);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immediately 
// after the thread starts running.

void EventThread::threadInitFunction()
{
   Prn::print(Prn::View11, "EventThread::threadInitFunction**********************");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immediately
// before the thread is terminated.

void EventThread::threadExitFunction()
{
   Prn::print(Prn::View11, "EventThread::threadExitFunction**********************");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void EventThread::executeProcessEventRecord(EventRecord* aEventRecord)
{
   Prn::print(Prn::View11, "ProcessEventRecord %d", aEventRecord->mEvtId);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace