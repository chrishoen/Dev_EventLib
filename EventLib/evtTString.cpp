/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include <stdarg.h>
#include <ctype.h>

#include "risProgramTime.h"

#include "evtEventThread.h"
#include "evtTString.h"

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

TString::TString()
{
   memset(&mSystemTime, 0, sizeof(mSystemTime));
   mProgramTime = 0.0;
   mSessionTime = 0.0;
   mString[0] = 0;
   mLogCode = 0;
   setTime();
}

TString::TString(const char* aString)
{
   memset(&mSystemTime, 0, sizeof(mSystemTime));
   mProgramTime = 0.0;
   mSessionTime = 0.0;
   strncpy(mString,aString,cMaxStringSize);
   mLogCode = 0;
   setTime();
}

TString::TString(std::string aString)
{
   memset(&mSystemTime, 0, sizeof(mSystemTime));
   mProgramTime = 0.0;
   mSessionTime = 0.0;
   strncpy(mString, aString.c_str(), cMaxStringSize);
   mLogCode = 0;
   setTime();
}

TString::TString(const TString& aRhs)
{
   mSystemTime = aRhs.mSystemTime;
   mProgramTime = aRhs.mProgramTime;
   mSessionTime = aRhs.mSessionTime;
   strncpy(mString, aRhs.mString, cMaxStringSize);
}
TString& TString::operator= (const TString& aRhs)
{
   mSystemTime = aRhs.mSystemTime;
   mProgramTime = aRhs.mProgramTime;
   mSessionTime = aRhs.mSessionTime;
   strncpy(mString, aRhs.mString, cMaxStringSize);
   return *this;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set the timestamp to the current time.

void TString::setTime()
{
   timespec_get(&mSystemTime, TIME_UTC);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get the timestamp as a string. This is passed in a local buffer.

char* TString::getTime(char* aBuffer)
{
   char tTemp[40];
   strftime(tTemp, 40, "%F %T", localtime(&mSystemTime.tv_sec));
   sprintf(aBuffer, "%s.%03ld", tTemp, mSystemTime.tv_nsec/1000000);

   return &aBuffer[0];
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Copy an input string to the member string.

void TString::puts(const char* aString)
{
   // Copy the input string.
   strncpy(mString, aString, cMaxStringSize);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Print to the member string.

void TString::print(const char* aFormat, ...)
{
   // Do a vsprintf with variable arg list into print string.
   int tPrintSize;
   va_list  ArgPtr;
   va_start(ArgPtr, aFormat);
   tPrintSize = vsnprintf(mString, cMaxStringSize, aFormat, ArgPtr);
   va_end(ArgPtr);
   mString[tPrintSize++] = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void TString::show(int aPF, char* aLabel)
{
   char tBuffer[100];
   Prn::print(aPF, "%s %20s %s", aLabel, getTime(tBuffer), mString);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Send this instance to the log file thread. The log file thread will
// eventually delete this instance. Do not use this instance after
// sending it. If this is not successful then it deletes itself.

void TString::sendToLogFile(int aLogCode)
{
   // Guard.
   bool tPass = true;
   if (gEventThread == 0)         tPass = false;

   // The log code is used for the log file prefix.
   this->mLogCode = aLogCode;

   // Try to write to the log file thread queue.
   if (tPass) tPass = gEventThread->tryWriteString(this);

   // If not successful then delete this instance.
   if (!tPass) delete this;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Create a new copy of this instance and send it to the log file
// thread. The log file thread will eventually delete the new instance.

void TString::copyToLogFile(int aLogCode)
{
   // Guard.
   if (gEventThread == 0) return;

   // Create a new copy of this instance.
   TString* tString = new TString(*this);

   // The log code is used for the log file prefix.
   tString->mLogCode = aLogCode;

   // Try to write to the log file thread queue.
   if (!gEventThread->tryWriteString(tString))
   {
      // not successful.
      delete tString;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

