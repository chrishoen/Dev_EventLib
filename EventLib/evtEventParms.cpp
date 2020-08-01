//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risCmdLineFile.h"

#define  _SOMEVIDEOPARMS_CPP_
#include "evtEventParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

EventParms::EventParms()
{
   reset();
}

void EventParms::reset()
{
   BaseClass::reset();
   //BaseClass::setFileName_RelAlphaFiles("/RisLib/Event_Parms.txt");
   //BaseClass::setFilePath("C:/aaa_prime/EventLib/Event_Parms.txt");
   BaseClass::setFilePath("/opt/prime/files/Event_Parms.txt");

   mDelaySpan1 = 0;
   mDelaySpan2 = 0;
   mEvtIdSpan1 = 0;
   mEvtIdSpan2 = 0;
   mCStateSpan1 = 0;
   mCStateSpan2 = 0;
   mSeveritySpan1 = 0;
   mSeveritySpan2 = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void EventParms::show()
{
   printf("\n");
   printf("EventParms************************************************ %s\n", mTargetSection);

   printf("\n");

   printf("\n");
   printf("DelaySpan                %-10d %-4d\n", mDelaySpan1, mDelaySpan2);
   printf("EvtIdSpan                %-10d %-4d\n", mEvtIdSpan1, mEvtIdSpan2);
   printf("CStateSpan               %-10d %-4d\n", mCStateSpan1, mCStateSpan2);
   printf("SeveritySpan             %-10d %-4d\n", mSeveritySpan1, mSeveritySpan2);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void EventParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("DelaySpan"))
   {
      mDelaySpan1 = aCmd->argInt(1);
      mDelaySpan2 = aCmd->argInt(2);
   }

   if (aCmd->isCmd("EvtIdSpan"))
   {
      mEvtIdSpan1 = aCmd->argInt(1);
      mEvtIdSpan2 = aCmd->argInt(2);
   }

   if (aCmd->isCmd("CStateSpan"))
   {
      mCStateSpan1 = aCmd->argInt(1);
      mCStateSpan2 = aCmd->argInt(2);
   }

   if (aCmd->isCmd("SeveritySpan"))
   {
      mSeveritySpan1 = aCmd->argInt(1);
      mSeveritySpan2 = aCmd->argInt(2);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void EventParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace