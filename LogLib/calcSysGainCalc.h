#pragma once

/*==============================================================================
System gain calculator.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <string>
#include "risThreadsSynch.h"

class FactoryTestRecordDA;
class FactoryTestRecordTTA;

namespace Calc
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class implements a the system gain calculator. It reads values from
// a json file, performs the system gain calculations, and writes values to
// the json file.

class SysGainCalc
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   // Some settings.
   static constexpr double cMaxAttenSetting = 15.5;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Json file path.
   std::string mFilePath;

   // Json file lock inter process mutex.
   Ris::Threads::NamedMutex mFileMutex;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Inputs from system.
   std::string mSystemType;
   int mRFPath;

   // Inputs from constants.
   double mDistUnitGain;

   // Inputs from factory test records.
   double mTTAGainA;
   double mTTAGainB;
   double mTTAGain;
   double mCtrlUnitGain;

   // Inputs from user. 
   double mAttenSetting;

   // Inputs from user.
   double mAntJumperLoss;
   double mAntFeedlineLoss;
   double mSurgeProtLoss;
   double mInsideJumperLoss;
   double mRxJumperLoss;
   double mRMCGain;
   double mDesiredRxGain;

   // Outputs.
   double mTotalRxLineLoss;
   double mCtrlOverallGain;
   double mRxOverallGain;
   double mMinPossibleRxGain;
   double mMaxPossibleRxGain;
   double mNewAttenSetting;

   // RSSI variables.
   double mRSSILevel;
   double mPage1Value;
   double mTestportCouplerLoss;
   double mTestportFeedlineLoss;
   double mTestportSurgeProtLoss;
   double mTestportJumperLoss;
   double mCtrlUnitTestportLoss;
   double mTestCable4Loss;
   double mReqGeneratorLevel;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // Constructor.
   SysGainCalc();

   // Set variable defaults.
   void setDefaults();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Lock the json file and read from it.
   void doReadModifyWriteBegin();

   // Perform the calculation, write to the json file, and unlock it.
   void doReadModifyWriteEnd();

   // Lock the json file, read from it, and unlock it.
   void doProtectedRead();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Read from the json file.
   void doRead();

   // Read from factory test records.
   void readFrom(FactoryTestRecordDA* aRecord);
   void readFrom(FactoryTestRecordTTA* aRecord);

   // Calculate system gain variables.
   void doCalculate();

   // Write to the json file.
   void doWrite();


   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Support.
   void show(int aPrintFilter = 0);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

