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
   mPendingCount = 0;
   mIgnoreFlag = false;
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
   mSeverity = aDefaultSeverity;
   mIgnoreFlag = true;
}

// Return true if these variables will change the record.
bool EventTableRecord::willChange(int aSeverity, bool aCState)
{
   return mSeverity != aSeverity || mCState != aCState;
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
   Prn::print(aPF, "CState                  %-s",     getCStateAsString());
   Prn::print(aPF, "Severity                %-s",     get_EvtSeverity_asString(mSeverity));
   Prn::print(aPF, "ArgString1              %-s",     mArgString1);
   Prn::print(aPF, "ArgString2              %-s",     mArgString2);
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// Update with an event record. Return true if the record was updated. 
// Return false if it was not. If this is for a type1 event then
// it is updated. If this is for a type2 event and the cstate or severity
// changed then it is updated.

bool EventTableRecord::update(EventRecord* aEventRecord)
{
   //************************************************************************
   //************************************************************************
   //************************************************************************
   // Test if the record needs to change.

   // Make the input event record consistent.
   if (aEventRecord->mCState && aEventRecord->mSeverity == cEvt_SevUseDefault)
   {
      // Overwrite the input event record severity with the table record
      // default.
      aEventRecord->mSeverity = mDefaultSeverity;
   }
   // Test if the table record needs to be updated.
   bool tChangeFlag = false;

   // For type1, always update.
   if (mType == cEvt_Type1) tChangeFlag = true;

   // For type2, test some variables. If they don't change, then don't 
   // update.
   if (mType == cEvt_Type2)
   {
      // Test for a change in variable.
      if (mCState != aEventRecord->mCState) tChangeFlag = true;

      // Test for a change in variable.
      if (mCState)
      {
         if (mSeverity != aEventRecord->mSeverity) tChangeFlag = true;
      }
   }

   //************************************************************************
   //************************************************************************
   //************************************************************************
   // Update with an event record.

   if (tChangeFlag)
   {
      // Set member variables.
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

   //************************************************************************
   //************************************************************************
   //************************************************************************
   // Done.

   // Decrement the pending count.
   Prn::print(Prn::View14, "PendingCount201 %d",
      mPendingCount.load());
   if (--mPendingCount < 0)
   {
      Prn::print(Prn::View11, "ATOMIC ERROR");
      mPendingCount.store(0);
   }

   // Return true if it changed.
   return tChangeFlag;
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

char* EventTableRecord::getLogFileShowString(char* aBuffer)
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
// Write a show string into a buffer string. Return a pointer to the buffer.

char* EventTableRecord::getAlarmFileShowString(char* aBuffer)
{
   // Do a string copy into the buffer string.
   strncpy(aBuffer, &mShowStringForAlarm[0], cMaxShowStringSize - 1);
   return aBuffer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a string for all of the variables.

std::string EventTableRecord::getLogFileJsonString()
{
   // Temp buffer.
   char tBuffer[200];

   // Json variable.
   Json::Value tJsonValue;

   // Copy members to the json variable.
   tJsonValue["TOA"] = get_timespec_asString(mTOA, tBuffer);
   tJsonValue["EvtId"] = mEvtId;
   tJsonValue["CState"] = getCStateAsString();
   tJsonValue["Severity"] = get_EvtSeverity_asString(mSeverity);
   tJsonValue["Show"] = getLogFileShowString(tBuffer);

   // Copy the json value to a string.
   std::string tString;
   Json::FastWriter tWriter;
   tString = tWriter.write(tJsonValue);
   return tString;

   // Return the string.
   return tString;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a string for all of the variables.

std::string EventTableRecord::getAlarmFileJsonString()
{
   // Temp buffer.
   char tBuffer[200];

   // Json variable.
   Json::Value tJsonValue;

   // Copy members to the json variable.
   tJsonValue["TOA"] = get_timespec_asString(mTOA, tBuffer);
   tJsonValue["EvtId"] = mEvtId;
   tJsonValue["CState"] = getCStateAsString();
   tJsonValue["Severity"] = get_EvtSeverity_asString(mSeverity);
   tJsonValue["Show"] = getAlarmFileShowString(tBuffer);

   // Copy the json value to a string.
   std::string tString;
   Json::FastWriter tWriter;
   tString = tWriter.write(tJsonValue);
   return tString;

   // Return the string.
   return tString;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace