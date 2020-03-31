//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "risFileJson.h"
#include "FactoryTestRecord.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

BaseFactoryTestRecord::BaseFactoryTestRecord()
{
   mValidFlag = false;
}

FactoryTestRecordDA::FactoryTestRecordDA()
{
  if (Ris::portableIsWindows())
  {
     mFilePath = "c:/aaa_cproc/files/FactoryTestRecordDA.json";
  }
  else
  {
     mFilePath = "/opt/prime/files/FactoryTestRecordDA.json";
  }

  mCtrlUnitTestportLoss = 0.0;
}

FactoryTestRecordTTA::FactoryTestRecordTTA()
{
   if (Ris::portableIsWindows())
   {
      mFilePath = "c:/aaa_cproc/files/FactoryTestRecordTTA.json";
   }
   else
   {
      mFilePath = "/opt/prime/files/FactoryTestRecordTTA.json";
   }

   mTTAGainA = 0.0;
   mTTAGainB = 0.0;
   mTestportCouplerLoss = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write to the json file.

void BaseFactoryTestRecord::doWriteToJsonFile()
{
   // Write to json file.
   Ris::doWriteJsonToFile(
      mJsonValue,           // Input
      mFilePath);           // Input
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read from the json file.

void BaseFactoryTestRecord::doReadFromJsonFile()
{
   // Json variables.
   Json::Value tJsonValue;

   // Guard.
   if (!Ris::portableFilePathExists(mFilePath.c_str())) return;

   // Read from json file.
   Ris::doReadJsonFromFile(
      mJsonValue,           // Output
      mFilePath);           // Input
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void BaseFactoryTestRecord::show(int aPF)
{
   Prn::print(aPF, "");
   Prn::print(aPF, "FilePath %s", mFilePath.c_str());
   std::cout << mJsonValue << std::endl;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read from string sent by da or tta.

void BaseFactoryTestRecord::test1(const std::string& aString)
{
   char tDelimiter = ',';
   std::stringstream tStream(aString);
   std::string tToken;

   while (std::getline(tStream, tToken, tDelimiter))
   {
      Prn::print(0, "STRTOK %s", tToken.c_str());
      size_t tIndex = tToken.find_first_of(':');
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read from string sent by da or tta.

void BaseFactoryTestRecord::fillWithCommandData(const std::string& aString)
{
   mJsonValue.clear();

   char tDelimiter = ',';
   std::stringstream tStream(aString);
   std::string tToken;

   while (std::getline(tStream, tToken, tDelimiter))
   {
      size_t tIndex = tToken.find_first_of(':');
      std::string tKey = tToken.substr(0, tIndex);
      std::string tValue = tToken.substr(tIndex + 1,aString.length() - 1);
      Prn::print(0, "%s %s", tKey.c_str(), tValue.c_str());
      mJsonValue[tKey] = std::stod(tValue);
   }

   mValidFlag = true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read from string sent by da or tta.

void FactoryTestRecordDA::fillWithCommandData(const std::string& aString)
{
   BaseClass::fillWithCommandData(aString);

   double tTIL794 = mJsonValue["TIL794"].asDouble();
   double tTIL809 = mJsonValue["TIL809"].asDouble();
   double tTIL824 = mJsonValue["TIL824"].asDouble();
   mCtrlUnitTestportLoss = (tTIL794 + tTIL809 + tTIL824) / 3.0;
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read from string sent by da or tta.

void FactoryTestRecordTTA::fillWithCommandData(const std::string& aString)
{
   BaseClass::fillWithCommandData(aString);

   double tAGA794 = mJsonValue["AGA794"].asDouble();
   double tAGA809 = mJsonValue["AGA809"].asDouble();
   double tAGA824 = mJsonValue["AGA824"].asDouble();
   mTTAGainA = (tAGA794 + tAGA809 + tAGA824) / 3.0;

   double tBGA794 = mJsonValue["BGA794"].asDouble();
   double tBGA809 = mJsonValue["BGA809"].asDouble();
   double tBGA824 = mJsonValue["BGA824"].asDouble();
   mTTAGainB = (tBGA794 + tBGA809 + tBGA824) / 3.0;

   double tTCP794 = mJsonValue["TCP794"].asDouble();
   double tTCP809 = mJsonValue["TCP809"].asDouble();
   double tTCP824 = mJsonValue["TCP824"].asDouble();
   mTestportCouplerLoss = (tTCP794 + tTCP809 + tTCP824) / 3.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

