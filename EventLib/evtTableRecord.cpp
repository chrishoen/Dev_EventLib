/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "evtTableRecord.h"

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
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
   mSeqNum = 0;
   mSeverity = cEvt_SevUseDefault;
   mCState = false;
   mDuration = 0.0;
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
   Prn::print(aPF, "SeqNum                  %-5d",    mSeqNum);
   Prn::print(aPF, "Severity                %-s",     get_EvtSeverity_asString(mSeverity));
   Prn::print(aPF, "CState                  %-s",     my_string_from_bool(mCState));
   Prn::print(aPF, "Duration                %-5.3f",  mDuration);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace