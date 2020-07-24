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
   int mEvtId = 0;
   int mType = 0;
   mStringForSet = 0;
   mStringForClear = 0;
   timespec mTOA = { 0 };
   mSeqNum = 0;
   mCState = false;
   mDuration = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace