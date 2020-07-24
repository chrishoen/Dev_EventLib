//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "evtEventDefs.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Evt
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return an event record variable as a string.

char* get_EvtType_asString(int aType)
{
   switch (aType)
   {
   case cEvt_Type1: return "Type1";
   case cEvt_Type2: return "Type2";
   }
   return "UNKNOWN";
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return an event record variable as a string.

char* get_EvtSeverity_asString(int aSeverity)
{
   switch (aSeverity)
   {
   case cEvt_SevUseDefault: return "UseDefault";
   case cEvt_SevInfo: return "Info";
   case cEvt_SevWarning: return "Warning";
   case cEvt_SevSevere: return "Severe";
   case cEvt_SevCritical: return "Critical";
   }
   return "UNKNOWN";
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get the timestamp as a string. This is passed in a local buffer.

char* get_timespec_asString(timespec aTimeSpec, char* aBuffer)
{
   char tTemp[40];
   strftime(tTemp, 40, "%F %T", localtime(&aTimeSpec.tv_sec));
   sprintf(aBuffer, "%s.%03ld", tTemp, aTimeSpec.tv_nsec / 1000000);

   return &aBuffer[0];
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace