//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "json.h"
#include "risFileJson.h"
#include "FactoryTestRecord.h"

#include "calcSysGainCalc.h"

namespace Calc
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

SysGainCalc::SysGainCalc()
{
   if (Ris::portableIsWindows())
   {
      mFilePath = "c:/aaa_cproc/files/sysgaincalc.json";
   }
   else
   {
      mFilePath = "/opt/prime/files/sysgaincalc.json";
   }
   mFileMutex.initialize("/sysgaincalc");

   mRFPath = 0;
   mAntJumperLoss = 0.0;
   mTTAGainA = 0.0;
   mTTAGainB = 0.0;
   mTTAGain = 0.0;
   mAntFeedlineLoss = 0.0;
   mSurgeProtLoss = 0.0;
   mInsideJumperLoss = 0.0;
   mTotalRxLineLoss = 0.0;
   mCtrlUnitGain = 0.0;
   mDistUnitGain = 0;
   mAttenSetting = 0.0;
   mCtrlOverallGain = 0.0;
   mRxJumperLoss = 0.0;
   mRMCGain = 0.0;
   mRxOverallGain = 0.0;
   mMinPossibleRxGain = 0.0;
   mMaxPossibleRxGain = 0.0;
   mDesiredRxGain = 0.0;
   mNewAttenSetting = 0.0;
   mRSSILevel = 0.0;
   mPage1Value = 0.0;;
   mTestportCouplerLoss = 0.0;
   mTestportFeedlineLoss = 0.0;
   mTestportSurgeProtLoss = 0.0;
   mTestportJumperLoss = 0.0;
   mCtrlUnitTestportLoss = 0.0;
   mTestCable4Loss = 0.0;
   mReqGeneratorLevel = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

// Lock the json file and read from it.
void SysGainCalc::doReadModifyWriteBegin()
{
   mFileMutex.lock();
   doRead();
}

// Perform the calculation, write to the json file, and unlock it.
void SysGainCalc::doReadModifyWriteEnd()
{
   doCalculate();
   doWrite();
   mFileMutex.unlock();
}

// Lock the json file, read from it, and unlock it.
void SysGainCalc::doProtectedRead()
{
   mFileMutex.lock();
   doRead();
   mFileMutex.unlock();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write to the json file.

void SysGainCalc::doWrite()
{
   // Do this first.
   mTTAGain = mRFPath == 0 ? mTTAGainA : mTTAGainB;

   // Json variables.
   Json::Value tJsonValue;

   // Copy members.
   tJsonValue["SystemType"] = mSystemType;
   tJsonValue["RFPath"] = mRFPath;
   tJsonValue["AntJumperLoss"] = mAntJumperLoss;
   tJsonValue["TTAGainA"] = mTTAGainA;
   tJsonValue["TTAGainB"] = mTTAGainB;
   tJsonValue["TTAGain"] = mTTAGain;
   tJsonValue["AntFeedlineLoss"] = mAntFeedlineLoss;
   tJsonValue["SurgeProtLoss"] = mSurgeProtLoss;
   tJsonValue["InsideJumperLoss"] = mInsideJumperLoss;
   tJsonValue["TotalRxLineLoss"] = mTotalRxLineLoss;
   tJsonValue["CtrlUnitGain"] = mCtrlUnitGain;
   tJsonValue["AttenSetting"] = mAttenSetting;
   tJsonValue["DistUnitGain"] = mDistUnitGain;
   tJsonValue["CtrlOverallGain"] = mCtrlOverallGain;
   tJsonValue["RxJumperLoss"] = mRxJumperLoss;
   tJsonValue["RMCGain"] = mRMCGain;
   tJsonValue["RxOverallGain"] = mRxOverallGain;
   tJsonValue["MinPossibleRxGain"] = mMinPossibleRxGain;
   tJsonValue["MaxPossibleRxGain"] = mMaxPossibleRxGain;
   tJsonValue["DesiredRxGain"] = mDesiredRxGain;
   tJsonValue["NewAttenSetting"] = mNewAttenSetting;
   tJsonValue["RSSILevel"] = mRSSILevel;
   tJsonValue["Page1Value"] = mPage1Value;
   tJsonValue["TestportCouplerLoss"] = mTestportCouplerLoss;
   tJsonValue["TestportFeedlineLoss"] = mTestportFeedlineLoss;
   tJsonValue["TestportSurgeProtLoss"] = mTestportSurgeProtLoss;
   tJsonValue["TestportJumperLoss"] = mTestportJumperLoss;
   tJsonValue["CtrlUnitTestportLoss"] = mCtrlUnitTestportLoss;
   tJsonValue["TestCable4Loss"] = mTestCable4Loss;
   tJsonValue["ReqGeneratorLevel"] = mReqGeneratorLevel;

   // Write to json file.
   Ris::doWriteJsonToFile(
      tJsonValue,           // Input
      mFilePath);           // Input
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read from the json file.

void SysGainCalc::doRead()
{
   // Json variables.
   Json::Value tJsonValue;

   // Guard.
   if (!Ris::portableFilePathExists(mFilePath.c_str())) return;

   // Read from json file.
   Ris::doReadJsonFromFile(
      tJsonValue,           // Output
      mFilePath);           // Input

   // Copy members.
   mSystemType = tJsonValue["SystemType"].asString();
   mRFPath = tJsonValue["RFPath"].asInt();
   mAntJumperLoss = tJsonValue["AntJumperLoss"].asDouble();
   mTTAGainA = tJsonValue["TTAGainA"].asDouble();
   mTTAGainB = tJsonValue["TTAGainB"].asDouble();
   mTTAGain = tJsonValue["TTAGain"].asDouble();
   mAntFeedlineLoss = tJsonValue["AntFeedlineLoss"].asDouble();
   mSurgeProtLoss = tJsonValue["SurgeProtLoss"].asDouble();
   mInsideJumperLoss = tJsonValue["InsideJumperLoss"].asDouble();
   mTotalRxLineLoss = tJsonValue["TotalRxLineLoss"].asDouble();
   mCtrlUnitGain = tJsonValue["CtrlUnitGain"].asDouble();
   mAttenSetting = tJsonValue["AttenSetting"].asDouble();
   mDistUnitGain = tJsonValue["DistUnitGain"].asDouble();
   mCtrlOverallGain = tJsonValue["CtrlOverallGain"].asDouble();
   mRxJumperLoss = tJsonValue["RxJumperLoss"].asDouble();
   mRMCGain = tJsonValue["RMCGain"].asDouble();
   mRxOverallGain = tJsonValue["RxOverallGain"].asDouble();
   mMinPossibleRxGain = tJsonValue["MinPossibleRxGain"].asDouble();
   mMaxPossibleRxGain = tJsonValue["MaxPossibleRxGain"].asDouble();
   mDesiredRxGain = tJsonValue["DesiredRxGain"].asDouble();
   mNewAttenSetting = tJsonValue["NewAttenSetting"].asDouble();
   mRSSILevel = tJsonValue["RSSILevel"].asDouble();
   mPage1Value = tJsonValue["Page1Value"].asDouble();
   mTestportCouplerLoss = tJsonValue["TestportCouplerLoss"].asDouble();
   mTestportFeedlineLoss = tJsonValue["TestportFeedlineLoss"].asDouble();
   mTestportSurgeProtLoss = tJsonValue["TestportSurgeProtLoss"].asDouble();
   mTestportJumperLoss = tJsonValue["TestportJumperLoss"].asDouble();
   mCtrlUnitTestportLoss = tJsonValue["CtrlUnitTestportLoss"].asDouble();
   mTestCable4Loss = tJsonValue["TestCable4Loss"].asDouble();
   mReqGeneratorLevel = tJsonValue["ReqGeneratorLevel"].asDouble();

   // Do this last.
   mTTAGain = mRFPath == 0 ? mTTAGainA : mTTAGainB;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read from factory test records.

void SysGainCalc::readFrom(FactoryTestRecordDA* aRecord)
{
   mCtrlUnitTestportLoss  = aRecord->mCtrlUnitTestportLoss;
}
void SysGainCalc::readFrom(FactoryTestRecordTTA* aRecord)
{
   mTTAGainA = aRecord->mTTAGainA;
   mTTAGainB = aRecord->mTTAGainB;
   mTestportCouplerLoss = aRecord->mTestportCouplerLoss;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SysGainCalc::show(int aPF)
{
   Prn::print(aPF, "");
   Prn::print(aPF, "FilePath %s", mFilePath.c_str());

   Prn::print(aPF, "SystemType              %6s",   mSystemType.c_str());
   Prn::print(aPF, "RFPath                  %6d",   mRFPath);
   Prn::print(aPF, "AntJumperLoss           %6.2f", mAntJumperLoss);
   Prn::print(aPF, "TTAGainA                %6.2f", mTTAGainA);
   Prn::print(aPF, "TTAGainB                %6.2f", mTTAGainB);
   Prn::print(aPF, "TTAGain                 %6.2f", mTTAGain);
   Prn::print(aPF, "AntFeedlineLoss         %6.2f", mAntFeedlineLoss);
   Prn::print(aPF, "SurgeProtLoss           %6.2f", mSurgeProtLoss);
   Prn::print(aPF, "InsideJumperLoss        %6.2f", mInsideJumperLoss);
   Prn::print(aPF, "TotalRxLineLoss         %6.2f", mTotalRxLineLoss);
   Prn::print(aPF, "CtrlUnitGain            %6.2f", mCtrlUnitGain);
   Prn::print(aPF, "DistUnitGain            %6.2f", mDistUnitGain);
   Prn::print(aPF, "CtrlOverallGain         %6.2f", mCtrlOverallGain);
   Prn::print(aPF, "RxJumperLoss            %6.2f", mRxJumperLoss);
   Prn::print(aPF, "RMCGain                 %6.2f", mRMCGain);
   Prn::print(aPF, "RxOverallGain           %6.2f", mRxOverallGain);
   Prn::print(aPF, "MinPossibleRxGain       %6.2f", mMinPossibleRxGain);
   Prn::print(aPF, "MaxPossibleRxGain       %6.2f", mMaxPossibleRxGain);
   Prn::print(aPF, "DesiredRxGain           %6.2f", mDesiredRxGain);
   Prn::print(aPF, "AttenSetting            %6.2f", mAttenSetting);
   Prn::print(aPF, "NewAttenSetting         %6.2f", mNewAttenSetting);
   Prn::print(aPF, "RSSILevel               %6.2f", mRSSILevel);
   Prn::print(aPF, "Page1Value              %6.2f", mPage1Value);
   Prn::print(aPF, "TestportCouplerLoss     %6.2f", mTestportCouplerLoss);
   Prn::print(aPF, "TestportFeedlineLoss    %6.2f", mTestportFeedlineLoss);
   Prn::print(aPF, "TestportSurgeProtLoss   %6.2f", mTestportSurgeProtLoss);
   Prn::print(aPF, "TestportJumperLoss      %6.2f", mTestportJumperLoss);
   Prn::print(aPF, "CtrlUnitTestportLoss    %6.2f", mCtrlUnitTestportLoss);
   Prn::print(aPF, "TestCable4Loss          %6.2f", mTestCable4Loss);
   Prn::print(aPF, "ReqGeneratorLevel       %6.2f", mReqGeneratorLevel);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
