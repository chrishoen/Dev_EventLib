
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
   Evt::EventTableRecord tRecord;
   tRecord.initialize(
      Evt::cEvtId_Test1,
      Evt::cEvt_Type2,
      Evt::cEvt_SevCritical,
      "Set Event for Test1",
      "Clear Event for Test1",
      "Alarm for Test1");

   tRecord.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   Evt::EventRecord tEventRecord;
   tEventRecord.mEvtId = Evt::cEvtId_Test1;
   tEventRecord.mCState = true;

   Evt::gEventStore.mEventTable.update(&tEventRecord);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   Evt::EventRecord* tEventRecord = new Evt::EventRecord(Evt::cEvtId_Test1,aCmd->argBool(1));

   tEventRecord->setArg1("%d", 101);
   tEventRecord->setArg2("%4.2f", 10.10);

   tEventRecord->sendToEventThread();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 0);
   aCmd->setArgDefault(2, false);
   aCmd->setArgDefault(3, 0);
   int tEvtId = aCmd->argInt(1);
   bool tCState = aCmd->argBool(2);
   int tSeverity = aCmd->argInt(3);

   Evt::EventRecord* tEventRecord = new Evt::EventRecord(tEvtId, tCState, tSeverity);

   tEventRecord->setArg1("%d", 101);
   tEventRecord->setArg2("%4.2f", 10.10);

   tEventRecord->sendToEventThread();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 0);
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

