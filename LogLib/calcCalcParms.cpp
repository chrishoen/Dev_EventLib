//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#define  _AUTOAUTOPARMS_CPP_
#include "calcCalcParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Calc
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

CalcParms::CalcParms()
{
   reset();
}

void CalcParms::reset()
{
   BaseClass::reset();
   BaseClass::setFilePath_RelativeToBaseDir("files/Calc_Parms.txt");

   mTimerPeriod = 0;
   mTestMode = 0;
   mInitialValueA = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void CalcParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void CalcParms::show()
{
   printf("\n");
   printf("CalcParms************************************************ %s\n", mTargetSection);
   printf("TimerPeriod            %10d\n", mTimerPeriod);
   printf("TestMode               %10d\n", mTestMode);
   printf("InitialValueA          %10.4f\n", mInitialValueA);
   printf("InitialValueB          %10.4f\n", mInitialValueB);
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void CalcParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("TimerPeriod"))           mTimerPeriod = aCmd->argInt(1);
   if (aCmd->isCmd("TestMode"))              mTestMode = aCmd->argInt(1);
   if (aCmd->isCmd("InitialValueA"))         mInitialValueA = aCmd->argDouble(1);
   if (aCmd->isCmd("InitialValueB"))         mInitialValueB = aCmd->argDouble(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace