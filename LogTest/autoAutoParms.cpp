//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#define  _AUTOAUTOPARMS_CPP_
#include "autoAutoParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Auto
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

AutoParms::AutoParms()
{
   reset();
}

void AutoParms::reset()
{
   BaseClass::reset();
   BaseClass::setFilePath_RelativeToBaseDir("files/Auto_Parms.txt");

   mTimerPeriod = 0;
   mTestMode = 0;
   mInitialValueA = 0.0;
   mAlphaFilterTs = 0.0;
   mAlphaFilterTc = 0.0;
   mFuzzyToCrispThreshLo = 0.0;
   mFuzzyToCrispThreshHi = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void AutoParms::expand()
{
   mThresholderParmsM2.mAlphaFilterTs = mAlphaFilterTs;
   mThresholderParmsM2.mAlphaFilterTc = mAlphaFilterTc;
   mThresholderParmsM1.mAlphaFilterTs = mAlphaFilterTs;
   mThresholderParmsM1.mAlphaFilterTc = mAlphaFilterTc;
   mThresholderParmsP1.mAlphaFilterTs = mAlphaFilterTs;
   mThresholderParmsP1.mAlphaFilterTc = mAlphaFilterTc;
   mThresholderParmsP2.mAlphaFilterTs = mAlphaFilterTs;
   mThresholderParmsP2.mAlphaFilterTc = mAlphaFilterTc;

   if (mThresholderParmsM2.mFuzzyToCrispThreshLo == 0.0) mThresholderParmsM2.mFuzzyToCrispThreshLo = mFuzzyToCrispThreshLo;
   if (mThresholderParmsM2.mFuzzyToCrispThreshHi == 0.0) mThresholderParmsM2.mFuzzyToCrispThreshHi = mFuzzyToCrispThreshHi;
   if (mThresholderParmsM1.mFuzzyToCrispThreshLo == 0.0) mThresholderParmsM1.mFuzzyToCrispThreshLo = mFuzzyToCrispThreshLo;
   if (mThresholderParmsM1.mFuzzyToCrispThreshHi == 0.0) mThresholderParmsM1.mFuzzyToCrispThreshHi = mFuzzyToCrispThreshHi;
   if (mThresholderParmsP1.mFuzzyToCrispThreshLo == 0.0) mThresholderParmsP1.mFuzzyToCrispThreshLo = mFuzzyToCrispThreshLo;
   if (mThresholderParmsP1.mFuzzyToCrispThreshHi == 0.0) mThresholderParmsP1.mFuzzyToCrispThreshHi = mFuzzyToCrispThreshHi;
   if (mThresholderParmsP2.mFuzzyToCrispThreshLo == 0.0) mThresholderParmsP2.mFuzzyToCrispThreshLo = mFuzzyToCrispThreshLo;
   if (mThresholderParmsP2.mFuzzyToCrispThreshHi == 0.0) mThresholderParmsP2.mFuzzyToCrispThreshHi = mFuzzyToCrispThreshHi;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void AutoParms::show()
{
   printf("\n");
   printf("AutoParms************************************************ %s\n", mTargetSection);
   printf("TimerPeriod            %10d\n", mTimerPeriod);
   printf("TestMode               %10d\n", mTestMode);
   printf("InitialValueA          %10.4f\n", mInitialValueA);
   printf("InitialValueB          %10.4f\n", mInitialValueB);

   printf("\n");
   mThresholderParmsM2.show("M2");
   mThresholderParmsM1.show("M1");
   mThresholderParmsP1.show("P1");
   mThresholderParmsP2.show("P2");
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void AutoParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("TimerPeriod"))           mTimerPeriod = aCmd->argInt(1);
   if (aCmd->isCmd("TestMode"))              mTestMode = aCmd->argInt(1);
   if (aCmd->isCmd("InitialValueA"))         mInitialValueA = aCmd->argDouble(1);
   if (aCmd->isCmd("InitialValueB"))         mInitialValueB = aCmd->argDouble(1);

   if (aCmd->isCmd("AlphaFilterTs"))         mAlphaFilterTs = aCmd->argDouble(1);
   if (aCmd->isCmd("AlphaFilterTc"))         mAlphaFilterTc = aCmd->argDouble(1);
   if (aCmd->isCmd("FuzzyToCrispThreshLo"))  mFuzzyToCrispThreshLo = aCmd->argDouble(1);
   if (aCmd->isCmd("FuzzyToCrispThreshHi"))  mFuzzyToCrispThreshHi = aCmd->argDouble(1);

   if (aCmd->isCmd("ThresholderM2"))     nestedPush(aCmd, &mThresholderParmsM2);
   if (aCmd->isCmd("ThresholderM1"))     nestedPush(aCmd, &mThresholderParmsM1);
   if (aCmd->isCmd("ThresholderP1"))     nestedPush(aCmd, &mThresholderParmsP1);
   if (aCmd->isCmd("ThresholderP2"))     nestedPush(aCmd, &mThresholderParmsP2);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace