#pragma once

/*==============================================================================
System gain calculator.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <string>

namespace NetCon
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class implements a the system gain calculator. It reads values from
// a json file, performs the system gain calculations, and writes values to
// the json file.

class NetCon
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
   double mSaveDesiredRxGain;

   // Outputs.
   double mTotalRxLineLoss;
   double mCtrlOverallGain;
   double mRxOverallGain;
   double mMinPossibleRxGain;
   double mMaxPossibleRxGain;
   double mNewAttenSetting;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // Constructor.
   NetCon();

   // Set variable defaults.
   void setDefaults();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Read from the json file.
   void doRead();

   // Calculate system gain variables.
   void doCalculate();

   // Write to the json file.
   void doWrite();

   // Accept the calcuation.
   void doAccept();

   // Cancel the calcuation.
   void doCancel();

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

