#include "stdafx.h"

#include "risThreadsProcess.h"
#include "risCmdLineConsole.h"
#include "evtEventThread.h"
#include "evtRandomTimerThread.h"

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

   Evt::gRandomTimerThread1 = new Evt::RandomTimerThread(1);
   Evt::gRandomTimerThread2 = new Evt::RandomTimerThread(2);
   Evt::gRandomTimerThread1->launchThread();
   Evt::gRandomTimerThread2->launchThread();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show program threads.

   Ris::Threads::showCurrentThreadInfo();
   if (Evt::gEventThread)         Evt::gEventThread->showThreadInfo();
   if (Evt::gRandomTimerThread1) Evt::gRandomTimerThread1->showThreadInfo();
   if (Evt::gRandomTimerThread2) Evt::gRandomTimerThread2->showThreadInfo();

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
   if (Evt::gRandomTimerThread1)   Evt::gRandomTimerThread1->shutdownThread();
   if (Evt::gRandomTimerThread2)   Evt::gRandomTimerThread2->shutdownThread();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Delete program threads.

   if (Evt::gEventThread)
   {
      delete Evt::gEventThread;
      Evt::gEventThread = 0;
   }

   if (Evt::gRandomTimerThread1)
   {
      delete Evt::gRandomTimerThread1;
      Evt::gRandomTimerThread1 = 0;
   }

   if (Evt::gRandomTimerThread2)
   {
      delete Evt::gRandomTimerThread2;
      Evt::gRandomTimerThread2 = 0;
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

