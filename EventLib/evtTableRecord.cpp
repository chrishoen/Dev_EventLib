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
   timespec mTOA = { 0 };
   mSeqNum = 0;
   mSeverity = cEvt_SevUseDefault;
   mCState = false;
   mDuration = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void EventTableRecord::show(int aPF)
{
   char tBuffer[40];
   Prn::print(aPF, "EventTableRecord********************************");
   Prn::print(aPF, "EvtId                   %5d", mEvtId);
   Prn::print(aPF, "Type                    %s", get_EvtType_asString(mType));
   Prn::print(aPF, "DefaultSeverity         %s", get_EvtSeverity_asString(mDefaultSeverity));

   Prn::print(aPF, "ShowStringForSet        %s", mShowStringForSet);
   Prn::print(aPF, "ShowStringForClear      %s", mShowStringForClear);
   Prn::print(aPF, "ShowStringForAlarm      %s", mShowStringForAlarm);
   Prn::print(aPF, "TOA                     %s", get_timespec_asString(mTOA,tBuffer));
   Prn::print(aPF, "SeqNum                  %5d", mSeqNum);
   Prn::print(aPF, "Severity                %s", get_EvtSeverity_asString(mSeverity));
   Prn::print(aPF, "CState                  %s", my_string_from_bool(mCState));
   Prn::print(aPF, "Duration                %5.3f", mDuration);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace