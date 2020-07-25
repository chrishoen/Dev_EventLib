#pragma once

/*==============================================================================
This file provides a set of constants that are use throughout the event
processing code. It also provides some common helper functions.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <time.h>

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Event types. Events are defined as one of two types.

// A type one event is a momentary event that does not have a boolean state
// variable associated with it. An example is "the batter hit the ball". It
// is analogous to an impulse or a dirac delta function. A type one event
// can only be set and has a duration of zero.
static const int cEvt_Type1 = 1;

// A type two event is a momentary event that does has a boolean state
// variable associated with it. An example is "Bob drank a cup of coffee". It
// is analogous to a pulse. The pulse involves two events: a rising edge and
// a falling edge. A type two event can be set and then cleared. The event is
// set when Bob starts drinking the coffee and is cleared when he is finished.
// The duration can be considered as a pulse width.
static const int cEvt_Type2 = 2;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Event severity. Associated with each event is a severity that defines 
// alarm status. Severe and Critical are used to classify active alarms.

static const int cEvt_SevUseDefault = 0;
static const int cEvt_SevInfo = 1;
static const int cEvt_SevWarning  = 2;
static const int cEvt_SevSevere   = 3;
static const int cEvt_SevCritical = 4;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Event identifier. Associated with each event is an identifier. These are
// in sequential order and are used to index into the event table, which is a 
// fixed size array of event table records. Care must be taken to keep these
// integers compact. The meaning of the events is not given here. They can be
// derived from inspecting the event table.

// Event identifiers.
static const int cEvtId_Test1 = 0;
static const int cEvtId_Test2 = 1;
static const int cEvtId_Test3 = 2;
static const int cEvtId_Test4 = 3;

// Maximum number of events. This defines the size of the event table.
static const int cEvt_MaxNumEvents = 4;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// More.

// Max table record or record argument size.
static const int cMaxRecordArgSize = 40;

// Max table record or record argument size.
static const int cMaxShowStringSize = 200;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers.

// Get a constant as a string.
char* get_EvtType_asString(int aType);
char* get_EvtSeverity_asString(int aSeverity);

// Get a timestamp as a string.
char* get_timespec_asString(timespec aTimeSpec, char* aBuffer);

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

