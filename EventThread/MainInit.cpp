#include "stdafx.h"

#include "risThreadsProcess.h"
#include "someThreadParms.h"
#include "logLogFileThread.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize program resources.

void main_initialize(int argc,char** argv)
{
   printf("LogThread Program**********************************************BEGIN\n");
   printf("LogThread Program**********************************************BEGIN\n");
   printf("LogThread Program**********************************************BEGIN\n\n");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize thread services.

   TS::reset();
   TS::setProgramName("LogThread");
   TS::setProgramPrintLevel(TS::PrintLevel(2, 2));
   TS::initialize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Enter process.

   // Enter process.
   Ris::Threads::enterProcessHigh();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize print facility.

   // Initialize print.
   Prn::resetPrint();
   Prn::useConsole(1);
   Prn::initializePrint();

   // Initialize print filters.
   Prn::setFilter(Prn::ThreadInit1,     true);
   Prn::setFilter(Prn::ThreadRun1,      true);
   Prn::setFilter(Prn::ThreadRun2,      false);
   Prn::setFilter(Prn::ThreadRun3,      false);
   Prn::setFilter(Prn::ThreadRun4,      false);
   Prn::setFilter(Prn::View11,          true,  1);
   Prn::setFilter(Prn::View12,          false, 1);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Read parameters files.

   // Read parameters files.
   Some::gThreadParms.reset();
   Some::gThreadParms.readSection("default");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize log facility.

   Log::initializeLogFile();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize program resources.

void main_finalize()
{
   // Finalize log facility.
   Log::finalizeLogFile();

   // Finalize print facility.
   Prn::finalizePrint();

   // Exit process.
   Ris::Threads::exitProcess();

   // Finalize thread services.
   TS::finalize();

   // done.
   printf("\n");
   printf("LogThread Program**********************************************END\n\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
