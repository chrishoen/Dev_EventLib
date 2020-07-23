#pragma once

/*==============================================================================
This file provides a set of constants that are use throughout the event
processing code.
==============================================================================*/

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
// variable associated with it. An example is "the batter hit the ball". It
// is analogous to a pulse. The pulse involves two events: a rising edge and
// a falling edge. A type two event can be set and then cleared. It has a
// duration that can be considered as the pulse width.
static const int cEvt_Type2 = 2;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Event severity. Associated with each event is a severity that defines 
// alarm status. Severe and Critical are used to classify active alarms.

static const int cEvt_SevInfo     = 0;
static const int cEvt_SevWarning  = 1;
static const int cEvt_SevSevere   = 2;
static const int cEvt_SevCritical = 3;

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

