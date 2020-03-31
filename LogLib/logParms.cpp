//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risCmdLineFile.h"
#include "logTString.h"

#define  _LOGPARMS_CPP_
#include "logParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Log
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

Parms::Parms()
{
   reset();
}

void Parms::reset()
{
   BaseClass::reset();
   BaseClass::setFileName_RelAlphaFiles("/Printer/LogFile_Parms.txt");
   mFullFilepath = false;

   mTimeType = 0;
   mLogFilename[0] = 0;
   mFlushModulo = 0;
   mFlushMode = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void Parms::show()
{
   char tBuffer[40];
   printf("\n");
   printf("Parms************************************************ %s\n", mTargetSection);

   printf("\n");
   printf("TimeType              %-10s\n", asStringTimeType(mTimeType));
   printf("LogFilename           %-10s\n", mLogFilename);
   printf("FullFilepath          %-10s\n", my_string_from_true(mFullFilepath));
   printf("FlushModulo           %-10d\n", mFlushModulo);
   printf("FlushMode             %-10d\n", mFlushMode);

   printf("\n");
   printf("PrintLevel            %-10s\n", mPrintLevel.asString(tBuffer));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void Parms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("TimeType"))
   {
      if (aCmd->isArgString(1, asStringTimeType(cLogSystemTime)))     mTimeType = cLogSystemTime;
      if (aCmd->isArgString(1, asStringTimeType(cLogProgramTime)))    mTimeType = cLogProgramTime;
      if (aCmd->isArgString(1, asStringTimeType(cLogSessionTime)))    mTimeType = cLogSessionTime;
   }

   if (aCmd->isCmd("LogFilename"))   aCmd->copyArgString(1, mLogFilename, cMaxStringSize);
   if (aCmd->isCmd("FullFilepath"))  mFullFilepath = aCmd->argBool(1);
   if (aCmd->isCmd("FlushModulo"))   mFlushModulo = aCmd->argInt(1);
   if (aCmd->isCmd("FlushMode"))     mFlushMode = aCmd->argInt(1);

   if (aCmd->isCmd("PrintLevel"))          mPrintLevel.readArgs(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void Parms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

char* Parms::asStringTimeType(int aTimeType)
{
   switch (aTimeType)
   {
   case cLogSystemTime: return "SystemTime";
   case cLogProgramTime: return "ProgramTime";
   case cLogSessionTime: return "SessionTime";
   default: return "UNKNOWN";
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace