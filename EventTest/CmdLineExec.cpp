
#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <time.h>
#include <thread>

#include "evtEventTableRecord.h"
#include "evtEventRecord.h"
#include "evtEventStore.h"
#include "evtEventThread.h"
#include "evtService.h"

#include "risCmdLineConsole.h"
#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

CmdLineExec::CmdLineExec()
{
}

void CmdLineExec::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class is the program command line executive. It processes user
// command line inputs and executes them. It inherits from the command line
// command executive base class, which provides an interface for executing
// command line commands. It provides an override execute function that is
// called by a console executive when it receives a console command line input.
// The execute function then executes the command.

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("GO1"))       executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))       executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))       executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))       executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))       executeGo5(aCmd);
   if (aCmd->isCmd("GO6"))       executeGo6(aCmd);
   if (aCmd->isCmd("GO7"))       executeGo7(aCmd);
   if (aCmd->isCmd("GO8"))       executeGo8(aCmd);
   if (aCmd->isCmd("GO9"))       executeGo9(aCmd);
   if (aCmd->isCmd("Show"))      executeShow(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   aCmd->setArgDefault(2, false);
   aCmd->setArgDefault(3, 0);
   int tEvtId = aCmd->argInt(1);
   bool tCState = aCmd->argBool(2);
   int tSeverity = aCmd->argInt(3);

   Evt::doSendEvent(tEvtId, tCState, tSeverity);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   aCmd->setArgDefault(2, false);
   aCmd->setArgDefault(3, 0);
   int tEvtId = aCmd->argInt(1);
   bool tCState = aCmd->argBool(2);
   int tSeverity = aCmd->argInt(3);

   Evt::EventRecord* tEventRecord = Evt::trySendEvent(tEvtId, tCState, tSeverity);
   if (tEventRecord)
   {
      tEventRecord->setArg1("%d", 101);
      tEventRecord->setArg2("%4.2f", 10.10);

      tEventRecord->sendToEventThread();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo7(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo8(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo9(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShow(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 0);
   int tEvtId = aCmd->argInt(1);
   Evt::gEventStore.mEventTable.showRecord(tEvtId, 0);
   Evt::gEventStore.mAlarmList.show(0);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

