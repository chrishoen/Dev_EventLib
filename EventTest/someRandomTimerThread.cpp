/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "someThreadParms.h"

#define  _SOMETIMERTHREAD_CPP_
#include "someRandomTimerThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

RandomTimerThread::RandomTimerThread(int aIdent)
   : mIdent(aIdent),
     mRandomGen(mRandomDevice()),
     mRandomDelay(gThreadParms.mDelaySpan1, gThreadParms.mDelaySpan2),
     mRandomEvtId(gThreadParms.mEvtIdSpan1, gThreadParms.mEvtIdSpan2),
     mRandomCState(gThreadParms.mCStateSpan1, gThreadParms.mCStateSpan2),
     mRandomSeverity(gThreadParms.mSeveritySpan1, gThreadParms.mSeveritySpan2)
{
   // Set base class thread parameters.
   BaseClass::setThreadName("RandomTimer1");
   BaseClass::setThreadPrintLevel(TS::PrintLevel(0, 0));

   mIdent = aIdent;
   mTPFlag = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immediately 
// after the thread starts running. It initializes SDL and creates the
// thread SDL window and associated resources.

void RandomTimerThread::threadInitFunction()
{
   Prn::print(Prn::View21, "RandomTimerThread::threadInitFunction %d", mIdent);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread run function. This is called by the base class immediately 
// after the thread init function. It runs a loop that waits on SDL
// events and processes posted events. The loop exits when it receives
// a quit event.

void RandomTimerThread::threadRunFunction()
{
   // Loop to wait for posted events and process them.
   int tCount = 0;
   while (true)
   {
      // Test for thread termination.
      if (BaseClass::mTerminateFlag) break;

      // Wait for a random delay.
      int tDelay    = mRandomDelay(mRandomGen);
      int tEvtId    = mRandomEvtId(mRandomGen);
      int tCState   = mRandomCState(mRandomGen);
      int tSeverity = mRandomSeverity(mRandomGen);
      Prn::print(Prn::View21, "Delay %4d %4d %4d %4d",tDelay,tEvtId,tCState,tSeverity);
      BaseClass::threadSleep(tDelay);

      // If not enabled then continue the loop.
      if (!mTPFlag) continue;

      tCount++;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immediately
// before the thread is terminated. It releases SDL resources and closes
// the thread SDL window.

void RandomTimerThread::threadExitFunction()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace