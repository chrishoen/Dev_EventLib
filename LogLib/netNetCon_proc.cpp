//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "json.h"
#include "risFileJson.h"

#include "netNetCon.h"

namespace NetCon
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set variable defaults.

void NetCon::setDefaults()
{
   // Inputs from factory test records.
   mSystemType = "ESS";
   mRFPath = 0;
   mTTAGainA = 31.0;
   mTTAGainB = 32.0;
   mTTAGain = 29.0;
   mCtrlUnitGain = -10.0;

   // Inputs from user.
   mAttenSetting = 3.0;

   // Inputs from user.
   mAntJumperLoss = 1.0;
   mAntFeedlineLoss = 1.0;
   mSurgeProtLoss = 1.0;
   mInsideJumperLoss = 1.0;
   mRxJumperLoss = 1.0;
   mRMCGain = 3.0;
   mDesiredRxGain = 10.0;

   doCalculate();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate system gain variables.

void NetCon::doCalculate()
{
   mTTAGain = mRFPath == 0 ? mTTAGainA : mTTAGainB;
   if (mSystemType == "ESS")
   {
      mDistUnitGain = 1.0;
      mRMCGain = 0.0;
   }
   else
   {
      mDistUnitGain = 0.0;
   }

   mTotalRxLineLoss =
      mAntFeedlineLoss + 
      mSurgeProtLoss +
      mInsideJumperLoss;

   mCtrlOverallGain = 
      mCtrlUnitGain +
      -mAttenSetting +
      mDistUnitGain;
   
   mMaxPossibleRxGain =
      -mAntJumperLoss +
      mTTAGain +
      -mAntFeedlineLoss +
      -mSurgeProtLoss +
      -mInsideJumperLoss +
      mCtrlUnitGain +
      mDistUnitGain +
      -mRxJumperLoss +
      mRMCGain;

   mMinPossibleRxGain =
      -cMaxAttenSetting;

   mRxOverallGain =
      mMaxPossibleRxGain +
      -mAttenSetting;

   mNewAttenSetting =
      mMaxPossibleRxGain +
      -mDesiredRxGain;

   mNewAttenSetting = floor(mNewAttenSetting * 2.0) / 2.0;

   if (mNewAttenSetting > cMaxAttenSetting)
   {
      mNewAttenSetting = cMaxAttenSetting;
   }
   if (mNewAttenSetting < 0)
   {
      mNewAttenSetting = 0;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Accept the calculation.

void NetCon::doAccept()
{
   mSaveDesiredRxGain = mDesiredRxGain;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Cancel the calculation.

void NetCon::doCancel()
{
   mDesiredRxGain = mSaveDesiredRxGain;
   doCalculate();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
