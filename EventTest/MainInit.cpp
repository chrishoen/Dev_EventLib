#include "stdafx.h"

#include "risThreadsProcess.h"
#include "evtEventStore.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize program resources.

void main_initialize(int argc,char** argv)
{
   printf("EventTest Program**********************************************BEGIN\n");
   printf("EventTest Program**********************************************BEGIN\n");
   printf("EventTest Program**********************************************BEGIN\n\n");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize thread services.

   TS::reset();
   TS::setProgramName("EventTest");
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

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize the event store.

   Evt::gEventStore.initialize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize program resources.

void main_finalize()
{
   // Finalize log facility.
   //Evt::finalizeLogFile();

   // Finalize print facility.
   Prn::finalizePrint();

   // Exit process.
   Ris::Threads::exitProcess();

   // Finalize thread services.
   TS::finalize();

   // done.
   printf("\n");
   printf("EventTest Program**********************************************END\n\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
