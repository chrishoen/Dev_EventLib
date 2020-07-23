
#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <time.h>
#include <thread>

#include "evtTString.h"
#include "evtEventThread.h"

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
   if (aCmd->isCmd("Parms"))     executeParms(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
void my_sleep()
{
   std::this_thread::sleep_for(std::chrono::seconds(1));
}

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   Evt::TString* tString = new Evt::TString;
   tString->puts("my_string");
   tString->show(0, "Go1");
   delete tString;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   Evt::TString* tString1 = new Evt::TString;
   tString1->puts("my_string1");
   my_sleep();
   Evt::TString* tString2 = new Evt::TString;
   tString2->puts("my_string2");

   tString1->show(0, "Go2");
   tString2->show(0, "Go2");
   delete tString1;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   Evt::TString* tString = new Evt::TString;
   tString->puts("Go3");
   tString->sendToLogFile();
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
   struct timespec ts;
   timespec_get(&ts, TIME_UTC);
   char buff[100];

   strftime(buff, sizeof buff, "%F %T", localtime(&ts.tv_sec));
   printf("Current time: %s.%09ld LOCAL\n", buff, ts.tv_nsec);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo8(Ris::CmdLineCmd* aCmd)
{
   struct timespec ts;
   timespec_get(&ts, TIME_UTC);
   struct tm* timeinfo = localtime(&ts.tv_sec);

   printf("%04d_%02d_%02d_%02d_%02d_%02d\n",
      timeinfo->tm_year + 1900,
      timeinfo->tm_mon + 1,
      timeinfo->tm_mday,
      timeinfo->tm_hour,
      timeinfo->tm_min,
      timeinfo->tm_sec);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo9(Ris::CmdLineCmd* aCmd)
{
   using namespace std::chrono;

   high_resolution_clock::time_point t1 = high_resolution_clock::now();

   my_sleep();

   high_resolution_clock::time_point t2 = high_resolution_clock::now();

   duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
   double tcount = time_span.count();

   Prn::print(0, "tcount %10.6f", tcount);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeParms(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

