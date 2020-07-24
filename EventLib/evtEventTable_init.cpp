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
      Evt::cEvtId_Test1,
      Evt::cEvt_Type2,
      Evt::cEvt_SevCritical,
      "Set Event for Test1",
      "Clear Event for Test1",
      "Alarm for Test1");

   initializeRecord(
      Evt::cEvtId_Test2,
      Evt::cEvt_Type2,
      Evt::cEvt_SevCritical,
      "Set Event for Test2",
      "Clear Event for Test2",
      "Alarm for Test2");

   initializeRecord(
      Evt::cEvtId_Test3,
      Evt::cEvt_Type2,
      Evt::cEvt_SevCritical,
      "Set Event for Test3",
      "Clear Event for Test3",
      "Alarm for Test3");

   initializeRecord(
      Evt::cEvtId_Test4,
      Evt::cEvt_Type2,
      Evt::cEvt_SevCritical,
      "Set Event for Test4",
      "Clear Event for Test4",
      "Alarm for Test4");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace