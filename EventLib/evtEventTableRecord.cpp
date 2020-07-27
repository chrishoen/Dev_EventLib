/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "evtEventTableRecord.h"

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

EventTableRecord::EventTableRecord()
{
   reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void EventTableRecord::reset()
{
   mEvtId = 0;
   mType = 0;
   mDefaultSeverity = cEvt_SevInfo;

   mShowStringForSet = 0;
   mShowStringForClear = 0;
   mShowStringForAlarm = 0;
   memset(&mTOA, 0, sizeof(mTOA));
   mSeverity = cEvt_SevUseDefault;
   mCState = false;
}

// Initialize.
void EventTableRecord::initialize(
   int aEvtId,
   int aType,
   int aDefaultSeverity,
   const char* aShowStringForSet,
   const char* aShowStringForClear,
   const char* aShowStringForAlarm)
{
   mEvtId = aEvtId;
   mType = aType;
   mDefaultSeverity = aDefaultSeverity;
   mShowStringForSet = aShowStringForSet;
   mShowStringForClear = aShowStringForClear;
   mShowStringForAlarm = aShowStringForAlarm;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void EventTableRecord::show(int aPF)
{
   char tBuffer[40];
   Prn::print(aPF, "EventTableRecord********************************");
   Prn::print(aPF, "EvtId                   %-5d",    mEvtId);
   Prn::print(aPF, "Type                    %-s",     get_EvtType_asString(mType));
   Prn::print(aPF, "DefaultSeverity         %-s",     get_EvtSeverity_asString(mDefaultSeverity));

   Prn::print(aPF, "ShowStringForSet        %-s",     mShowStringForSet);
   Prn::print(aPF, "ShowStringForClear      %-s",     mShowStringForClear);
   Prn::print(aPF, "ShowStringForAlarm      %-s",     mShowStringForAlarm);
   Prn::print(aPF, "TOA                     %s",      get_timespec_asString(mTOA,tBuffer));
   Prn::print(aPF, "Severity                %-s",     get_EvtSeverity_asString(mSeverity));
   Prn::print(aPF, "CState                  %-s",     getCStateAsString());
   Prn::print(aPF, "ArgString1              %-s",     mArgString1);
   Prn::print(aPF, "ArgString2              %-s",     mArgString2);
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Update with an event record.

void EventTableRecord::update(EventRecord* aEventRecord)
{
   mEvtId = aEventRecord->mEvtId;
   mTOA = aEventRecord->mTOA;

   if (aEventRecord->mSeverity != cEvt_SevUseDefault)
   {
      mSeverity = aEventRecord->mSeverity;
   }

   mCState = aEventRecord->mCState;

   strncpy(mArgString1, aEventRecord->mArgString1, cMaxRecordArgSize);
   strncpy(mArgString2, aEventRecord->mArgString2, cMaxRecordArgSize);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write a show string into a buffer string. Return a pointer to the buffer.

const char* EventTableRecord::getCStateAsString()
{
   // For type1.
   if (mType == cEvt_Type1) return "";
   // For type2, based on the cstate.
   if (mType == cEvt_Type2)
   {
      if (mCState) return "Active";
      else return "Inactive";
   }

   return "none";
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write a show string into a buffer string. Return a pointer to the buffer.

char* EventTableRecord::getShowString(char* aBuffer)
{
   // Point to the correct source string, based on the variables.
   const char* tSource = 0;
   // For type1, always use the first string.
   if (mType == cEvt_Type1) tSource = &mShowStringForSet[0];
   // For type2, based on the cstate, use either the first of second string.
   if (mType == cEvt_Type2)
   {
      if (mCState) tSource = &mShowStringForSet[0];
      else tSource = &mShowStringForClear[0];
   }

   // Do a string print into the buffer string, pass in the two armgument strings.
   snprintf(aBuffer, cMaxShowStringSize - 1, tSource, &mArgString1[0], &mArgString2[0]);
   return aBuffer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a json value for all of the variables.

Json::Value EventTableRecord::getLogFileJsonValue()
{
   // Temp buffer.
   char tBuffer[200];

   // Json variables.
   Json::Value tJsonValue;

   // Copy members.
   tJsonValue["TOA"] = get_timespec_asString(mTOA, tBuffer);
   tJsonValue["EvtId"] = mEvtId;
   tJsonValue["Severity"] = mSeverity;
   tJsonValue["CState"] = getCStateAsString();
   tJsonValue["Show"] = getShowString(tBuffer);

   return tJsonValue;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a string with json for all of the variables.

std::string EventTableRecord::getLogFileJsonString()
{
   // Json variable.
   Json::Value tJsonValue = getLogFileJsonValue();

   std::string tString;
   Json::FastWriter tWriter;
   tString = tWriter.write(tJsonValue);
   return tString;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace