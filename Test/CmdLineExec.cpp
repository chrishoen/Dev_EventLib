#include "stdafx.h"

#include <string>
#include <ctime>
#include <time.h>
#include <stdarg.h>


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
   if(aCmd->isCmd("RESET"  ))  reset();
   if(aCmd->isCmd("GO1"    ))  executeGo1(aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2(aCmd);
   if(aCmd->isCmd("GO3"    ))  executeGo3(aCmd);
   if(aCmd->isCmd("GO4"    ))  executeGo4(aCmd);
   if(aCmd->isCmd("GO5"    ))  executeGo5(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   struct timespec tSystemTime;
   timespec_get(&tSystemTime, TIME_UTC);

   char tTemp1[40];
   char tTemp2[40];
   strftime(tTemp1, 40, "%F %T", localtime(&tSystemTime.tv_sec));
   sprintf(tTemp2, "%s.%03ld", tTemp1, tSystemTime.tv_nsec / 1000000);

   Prn::print(0, "GO1 %s",tTemp2);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   // Tue, 31 Mar 2020 14:09:27
   struct timespec tSystemTime;
   timespec_get(&tSystemTime, TIME_UTC);

   char tTemp1[40];
   char tTemp2[40];
   strftime(tTemp1, 40, "%a, %d %b %Y %T", localtime(&tSystemTime.tv_sec));
   sprintf(tTemp2, "%s.%03ld", tTemp1, tSystemTime.tv_nsec / 1000000);

   Prn::print(0, "GO1 %s", tTemp2);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   time_t currtime;

   struct tm* timeinfo;

   time(&currtime);

   timeinfo = gmtime(&currtime);

   time_t utc = mktime(timeinfo);

   timeinfo = localtime(&currtime);

   time_t local = mktime(timeinfo);



   // Get offset in hours from UTC

   double offsetFromUTC = difftime(utc, local) / 3600;



   // Adjust for DST

   if (timeinfo->tm_isdst)

   {

      offsetFromUTC -= 1;

   }

   Prn::print(0, "%6.2f", offsetFromUTC);


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

