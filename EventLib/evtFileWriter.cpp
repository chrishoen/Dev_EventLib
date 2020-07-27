/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include <stdarg.h>
#include <ctype.h>

#include "evtEventThread.h"
#include "evtFileWriter.h"

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

FileWriter::FileWriter()
{
   reset();
}

FileWriter::FileWriter(int aEvtId)
{
   reset();
   mEvtId = aEvtId;
}
FileWriter::FileWriter(int aEvtId, bool aCState)
{
   reset();
   mEvtId = aEvtId;
   mCState = aCState;
}
FileWriter::FileWriter(int aEvtId, bool aCState, int aSeverity)
{
   reset();
   mEvtId = aEvtId;
   mCState = aCState;
   mSeverity = aSeverity;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void FileWriter::reset()
{
   mEvtId = 0;
   timespec_get(&mTOA, TIME_UTC);
   mSeverity = cEvt_SevUseDefault;
   mCState = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set the argumant strings via a variable arg list using vnsprintf.

void FileWriter::setArg1(const char* aFormat, ...)
{
   // Do a vsprintf with variable arg list into the argument string.
   int tPrintSize = 0;
   va_list  ArgPtr;
   va_start(ArgPtr, aFormat);
   tPrintSize = vsnprintf(mArgString1, cMaxRecordArgSize - 1, aFormat, ArgPtr);
   va_end(ArgPtr);
   mArgString1[tPrintSize++] = 0;
}

void FileWriter::setArg2(const char* aFormat, ...)
{
   // Do a vsprintf with variable arg list into the argument string.
   int tPrintSize = 0;
   va_list  ArgPtr;
   va_start(ArgPtr, aFormat);
   tPrintSize = vsnprintf(mArgString2, cMaxRecordArgSize - 1, aFormat, ArgPtr);
   va_end(ArgPtr);
   mArgString1[tPrintSize++] = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void FileWriter::show(int aPF)
{
   char tBuffer[40];
   Prn::print(aPF, "FileWriter********************************");
   Prn::print(aPF, "EvtId                   %-5d",    mEvtId);

   Prn::print(aPF, "TOA                     %s",      get_timespec_asString(mTOA,tBuffer));
   Prn::print(aPF, "Severity                %-s",     get_EvtSeverity_asString(mSeverity));
   Prn::print(aPF, "CState                  %-s",     my_string_from_bool(mCState));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Send this instance to the event thread. The event thread will
// eventually delete this instance. Do not use this instance after
// sending it. If this is not successful then it deletes itself.

void FileWriter::sendToEventThread()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace