/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "autoAutoParms.h"
#include "autoSwitchLogic.h"

namespace Auto
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

SwitchLogic::SwitchLogic()
{
   mClassA = cClass_None;
   mClassB = cClass_None;
   mClassChangeFlagA = false;
   mClassChangeFlagB = false;
   mClassChangeFlag = false;
   mPathChangeFlag = false;

   mFirstFlag = true;
   mCount = 0;
   mValueA = 0.0;
   mValueB = 0.0;

   mNextPath = 0;
   mCurrentPath = 0;
   mRequestedPath = 0;

   mClassifierA.initialize();
   mClassifierB.initialize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void SwitchLogic::initialize()
{
   mClassifierA.initialize();
   mClassifierB.initialize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void SwitchLogic::doRequestPathA()
{
   mRequestedPath = cPath_A;
}

void SwitchLogic::doRequestPathB()
{
   mRequestedPath = cPath_B;
}


//******************************************************************************
//******************************************************************************
//******************************************************************************

void SwitchLogic::doUpdateA(double aValue)
{
   mValueA = aValue;
   mClassifierA.doClassify(mValueA, mClassA, mClassChangeFlagA);
   mFuzzyConfidence = mClassifierA.mFuzzyConfidence && mClassifierB.mFuzzyConfidence;
   mClassChangeFlag = mClassChangeFlagA || mClassChangeFlagB;
}

void SwitchLogic::doUpdateB(double aValue)
{
   mValueB = aValue;
   mClassifierB.doClassify(mValueB, mClassB, mClassChangeFlagB);
   mFuzzyConfidence = mClassifierA.mFuzzyConfidence && mClassifierB.mFuzzyConfidence;
   mClassChangeFlag = mClassChangeFlagA || mClassChangeFlagB;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SwitchLogic::show()
{
   char tString[200];
   sprintf(tString, "%4d    R %1d   F %1d %1d    V %6.4f %6.4f    FL %6.4f %6.4f     CS %2d %2d     P  %1d " ,
      mCount,
      mRequestedPath,
      mAmpFailedA,
      mAmpFailedB,
      mValueA,
      mValueB,
      mClassifierA.mFuzzyConfidence.mX,
      mClassifierB.mFuzzyConfidence.mX,
      mClassA,
      mClassB,
      mCurrentPath);

   if (mAmpFailedA && mAmpFailedPrintCatchA == 0)
   {
      strcat(tString, " AMP A FAILURE");
      mAmpFailedPrintCatchA++;
   }

   if (mAmpFailedB && mAmpFailedPrintCatchB == 0)
   {
      strcat(tString, " AMP B FAILURE");
      mAmpFailedPrintCatchB++;
   }

   if (mClassChangeFlag)
   {
      strcat(tString, " CLASS CHANGE");
   }
   
   if (mPathChangeFlag)
   {
      strcat(tString, " PATH CHANGE");
   }
   Prn::print(Prn::View11, "%s", tString);
   mCount++;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace