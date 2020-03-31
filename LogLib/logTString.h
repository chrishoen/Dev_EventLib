#pragma once
/*==============================================================================
Time stamped string class.
==============================================================================*/

#include "risByteContent.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <string>
#include <ctime>
#include <time.h>

namespace Log
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constants.

// Timestamp types.
static const int cLogSystemTime  = 1;
static const int cLogProgramTime = 2;
static const int cLogSessionTime = 3;

// Log prefix type.
static const int cLogAsAny     = 0;
static const int cLogAsInput   = 1;
static const int cLogAsNak     = 2;
static const int cLogAsOutput  = 3;
static const int cLogAsSlice   = 4;
static const int cLogAsPWM     = 5;
static const int cLogAsTest    = 6;
static const int cLogAsCMarker = 7;
static const int cLogAsInfo    = 8;
static const int cLogAsError   = 9;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encalsulates a time stamped string. It contains a time stamp
// that can be set by various sources (system time, program time, session
// time) and a string. Instances of this class are used to write entries
// to log files.

class TString
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   static const int cMaxStringSize = 200;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // System time obtained from the system clock.
   // Time is absolute local time.
   struct timespec mSystemTime;

   // Program time obtained from high resolution clock.
   // Time is seconds since program startup.
   double mProgramTime;

   // Program time obtained from high resolution clock.
   // Time is seconds since session start.
   double mSessionTime;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Null terminated string.
   char mString[cMaxStringSize];

   // Log code. Input, Output, Info, Error, ...
   int mLogCode;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   TString();
   TString(const char* aString);
   TString(std::string aString);

   // Copy constructor and assignment operator.
   TString(const TString& aRhs);
   TString& operator= (const TString& aRhs);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Set the timestamp to the current time.
   void setTime();

   // Get the timestamp as a string. This is passed in a local buffer.
   char* getTime(char* aBuffer);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Copy an input string to the member string.
   void puts(const char* aString);

   // Print to the member string.
   void print(const char* aFormat, ...);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Send this instance to the log file thread. The log file thread will
   // eventually delete this instance. Do not use this instance after
   // sending it. If this is not successful then it deletes itself.
   void sendToLogFile(int aLogCode = cLogAsAny);

   // Create a new copy of this instance and send it to the log file
   // thread. The log file thread will eventually delete the new instance.
   void copyToLogFile(int aLogCode = cLogAsAny);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Show.
   void show(int aPrintFilter,char* aLabel);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace




