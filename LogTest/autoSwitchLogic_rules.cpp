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

void SwitchLogic::checkAmpFail()
{
      // Amp A Failure Latch
      // if amplifier A is critical and hasn't been before, latch in the failure, so that rules forbid its use
      if (abs(mClassA) == 2 && !mAmpFailedA)
      {
         mAmpFailedA = 1; // this is the only place and time that this flag can be written, this can only happen once //
         mAmpFailedPrintCatchA = 0; // this allows print statement
      }

      // Amp B Failure Latch
      // if amplifier B is critical and hasn't been before, latch in the failure so that rules forbid its use
      if (abs(mClassB) == 2 && !mAmpFailedB)
      {
         mAmpFailedB = 1; // this is the only place and time that this flag can be written, this can only happen once
         mAmpFailedPrintCatchB = 0; // this allows print statement
      }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void SwitchLogic::doEvaluateRules()
{
   // RULE 1.
   // If bypass is true, then stay in bypass forever
   if (mCurrentPath == cPath_Bypass)
   {
      return;
   }

   // RULE 2.
   // If both amps failed then set bypass.
   if (mAmpFailedA && mAmpFailedB)
   {
      mNextPath = cPath_Bypass;
      return;
   }

   // RULE 3
   // If path A has failed, then select B.
   if (mAmpFailedA)
   {
      mNextPath = cPath_B;
         return;
   }

   // RULE 4
   // If path B has failed, then select A.
   if (mAmpFailedB)
   {
      mNextPath = cPath_A;
      return;
   }

   // RULE 5.
   // If the states are the same (including polarity) then set path to the requested path. At this level of logic, single or double failures have already returned.
   // This means that the classes at this level can only be -1,0, or +1 (because -2 and +2 cases are caught above)
   if (mClassA == mClassB)
   {
      mNextPath = mRequestedPath;
      return;
   }

   // RULE 6.
   // IF the alarms are not the same polarity 
   if (abs(mClassA) == abs(mClassB) && mClassA > mClassB)
   {
      mNextPath = cPath_A;
      return;
   }

   // RULE 7.
   // IF the alarms are not the same polarity
   if (abs(mClassA) == abs(mClassB) && mClassA < mClassB)
   {
      mNextPath = cPath_B;
      return;
   }

   // RULE 8.
   // If A is better than B then switch to A.
   if (abs(mClassA) < abs(mClassB))
   {
      mNextPath = cPath_A;
      return;
   }

   // RULE 9.
   // Therefore B is better than A so switch to B.
   mNextPath = cPath_B;
   return;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void SwitchLogic::doEvaluateSwitch()
{
   mPathChangeFlag = mCurrentPath != mNextPath;
   mCurrentPath = mNextPath;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace