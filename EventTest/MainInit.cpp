#include "stdafx.h"

#include "risThreadsProcess.h"
#include "evtEventParms.h"
#include "smShare.h"
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
   // Read parameters files.

   // Read parameters files.
   Evt::gEventParms.reset();
   Evt::gEventParms.readSection("default");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize print facility.

   // Initialize print.

   if (Evt::gEventParms.mPrintCode == 0)
   {
      Prn::resetPrint();
      Prn::useConsole(1);
      Prn::useConsole(2);
      Prn::initializePrint();

      Prn::setFilter(Prn::View11, true, 1);
      Prn::setFilter(Prn::View12, false, 1);
      Prn::setFilter(Prn::View21, true, 2);
      Prn::setFilter(Prn::View22, false, 2);
   }
   else
   {
      Prn::resetPrint();
      Prn::initializePrint();

      Prn::setFilter(Prn::View11, true);
      Prn::setFilter(Prn::View12, false);
      Prn::setFilter(Prn::View21, false);
      Prn::setFilter(Prn::View22, false);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize.

   // Initialize shared memory.
   SM::initializeShare();

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
