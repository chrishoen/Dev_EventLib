/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "evtEventTable.h"

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize a record.

void EventTable::initializeRecord(
   int aEvtId,
   int aType,
   int aDefaultSeverity,
   const char* aShowStringForSet,
   const char* aShowStringForClear,
   const char* aShowStringForAlarm)
{
   mArray[aEvtId].initialize(
      aEvtId,
      aType,
      aDefaultSeverity,
      aShowStringForSet,
      aShowStringForClear,
      aShowStringForAlarm);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize all records.

void EventTable::initialize()
{
   initializeRecord(
      Evt::cEvtId_Test0,
      Evt::cEvt_Type1,
      Evt::cEvt_SevInfo,
      "Set Event for Test0 %s %s",
      "",
      "");

   initializeRecord(
      Evt::cEvtId_Test1,
      Evt::cEvt_Type2,
      Evt::cEvt_SevCritical,
      "Set Event for Test1 %s %s",
      "Clear Event for Test1",
      "ALARM FOR TEST1");

   initializeRecord(
      Evt::cEvtId_Test2,
      Evt::cEvt_Type2,
      Evt::cEvt_SevCritical,
      "Set Event for Test2",
      "Clear Event for Test2",
      "ALARM FOR TEST2");

   initializeRecord(
      Evt::cEvtId_Test3,
      Evt::cEvt_Type2,
      Evt::cEvt_SevCritical,
      "Set Event for Test3",
      "Clear Event for Test3",
      "ALARM FOR TEST3");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace