//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "json.h"
#include "risFileJson.h"

#include "calcSysGainCalc.h"

namespace Calc
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set variable defaults.

void SysGainCalc::setDefaults()
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

   mRSSILevel = -90.0;
   mTestportCouplerLoss = 1.0;
   mTestportFeedlineLoss = 1.0;
   mTestportSurgeProtLoss = 1.0;
   mTestportJumperLoss = 1.0;
   mCtrlUnitTestportLoss = 1.0;
   mTestCable4Loss = 1.0;

   doCalculate();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate system gain variables.

void SysGainCalc::doCalculate()
{
   mTTAGain = mRFPath == 0 ? mTTAGainA : mTTAGainB;
   if (mSystemType == "ESS")
   {
      mDistUnitGain = 0.0;
   }
   else
   {
      mDistUnitGain = 1.0;
      mRMCGain = 0.0;
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
      mMaxPossibleRxGain +
      -cMaxAttenSetting;

   mRxOverallGain =
      mMaxPossibleRxGain +
      -mAttenSetting;

   mNewAttenSetting =
      mMaxPossibleRxGain +
      -mDesiredRxGain;

   mNewAttenSetting = round(mNewAttenSetting * 2.0) / 2.0;

   if (mNewAttenSetting > cMaxAttenSetting)
   {
      mNewAttenSetting = cMaxAttenSetting;
   }
   if (mNewAttenSetting < 0)
   {
      mNewAttenSetting = 0;
   }

   mPage1Value =
      mRSSILevel +
      mRxJumperLoss +
      -mCtrlOverallGain +
      mInsideJumperLoss +
      mSurgeProtLoss +
      mAntFeedlineLoss +
      -mTTAGain;

   mReqGeneratorLevel =
      mRSSILevel +
      mRxJumperLoss +
      -mCtrlOverallGain + 
      mInsideJumperLoss +
      mSurgeProtLoss +
      mAntFeedlineLoss +
      -mTTAGain +
      mTestportCouplerLoss +
      mTestportFeedlineLoss +
      mTestportSurgeProtLoss +
      mTestportJumperLoss +
      mCtrlUnitTestportLoss +
      mTestCable4Loss;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
