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
   mDefaultSevarity = cEvt_SevInfo;

   mShowStringForSet = 0;
   mShowStringForClear = 0;
   timespec mTOA = { 0 };
   mSeqNum = 0;
   mSevarity = cEvt_SevUseDefault;
   mCState = false;
   mDuration = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace