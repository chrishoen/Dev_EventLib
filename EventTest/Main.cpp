#include "stdafx.h"

#include "risThreadsProcess.h"
#include "risCmdLineConsole.h"
#include "evtEventThread.h"
#include "someRandomTimerThread.h"

#include "CmdLineExec.h"

#include "MainInit.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

int main(int argc,char** argv)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Begin program.

   main_initialize(argc,argv);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Launch program threads.

   Evt::gEventThread = new Evt::EventThread;
   Evt::gEventThread->launchThread();

   Some::gRandomTimerThread1 = new Some::RandomTimerThread(1);
   Some::gRandomTimerThread1->launchThread();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show program threads.

   Ris::Threads::showCurrentThreadInfo();
   if (Evt::gEventThread)       Evt::gEventThread->showThreadInfo();
   if (Some::gRandomTimerThread1) Some::gRandomTimerThread1->showThreadInfo();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Execute user command line executive, wait for user to exit.

   CmdLineExec* tExec = new CmdLineExec;
   Ris::gCmdLineConsole.execute(tExec);
   delete tExec;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Shutdown program threads.

   if (Evt::gEventThread)   Evt::gEventThread->shutdownThread();
   if (Some::gRandomTimerThread1)   Some::gRandomTimerThread1->shutdownThread();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Delete program threads.

   if (Evt::gEventThread)
   {
      delete Evt::gEventThread;
      Evt::gEventThread = 0;
   }

   if (Some::gRandomTimerThread1)
   {
      delete Some::gRandomTimerThread1;
      Some::gRandomTimerThread1 = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // End program.

   main_finalize();
   return 0;

   printf("press enter\n");
   getchar();
   return 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

