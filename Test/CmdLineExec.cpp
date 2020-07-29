#include "stdafx.h"

#include <string>
#include <ctime>
#include <time.h>
#include <stdarg.h>

#include <set> 
#include <iterator> 

#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

CmdLineExec::CmdLineExec()
{
}

void CmdLineExec::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class is the program command line executive. It processes user
// command line inputs and executes them. It inherits from the command line
// command executive base class, which provides an interface for executing
// command line commands. It provides an override execute function that is
// called by a console executive when it receives a console command line input.
// The execute function then executes the command.

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"  ))  reset();
   if(aCmd->isCmd("GO1"    ))  executeGo1(aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2(aCmd);
   if(aCmd->isCmd("GO3"    ))  executeGo3(aCmd);
   if(aCmd->isCmd("GO4"    ))  executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))  executeGo5(aCmd);
   if (aCmd->isCmd("GO6"))  executeGo6(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   struct timespec tSystemTime;
   timespec_get(&tSystemTime, TIME_UTC);

   char tTemp1[40];
   char tTemp2[40];
   strftime(tTemp1, 40, "%F %T", localtime(&tSystemTime.tv_sec));
   sprintf(tTemp2, "%s.%03ld", tTemp1, tSystemTime.tv_nsec / 1000000);

   Prn::print(0, "GO1 %s",tTemp2);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   // Tue, 31 Mar 2020 14:09:27
   struct timespec tSystemTime;
   timespec_get(&tSystemTime, TIME_UTC);

   char tTemp1[40];
   char tTemp2[40];
   strftime(tTemp1, 40, "%a, %d %b %Y %T", localtime(&tSystemTime.tv_sec));
   sprintf(tTemp2, "%s.%03ld", tTemp1, tSystemTime.tv_nsec / 1000000);

   Prn::print(0, "GO1 %s", tTemp2);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   std::set<int, std::less<int>> tSet;
   tSet.insert(1);
   tSet.insert(2);
   tSet.insert(3);
   tSet.insert(4);

   std::set<int, std::less<int>>::iterator tItr;

   for (tItr = tSet.begin(); tItr != tSet.end(); ++tItr)
   {
      Prn::print(0,"%d", *tItr);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
void FindWord(char* word, char* file) {
   char line[1024];
   FILE* fp = fopen(file, "r");
   while (fgets(line, sizeof(line), fp) != NULL)
   {
      if (strstr(line, word) != NULL)
      {
         printf("%s", line);
      }
   }
}

void get_value_from_json(const char* key) {
   FILE* j;
   char line[200];
   size_t len = 0;
   //size_t read;
   char* ret;
   j = fopen("/mnt/flash/snmp/snmpd.json", "r");
   if (!j) {
      return;
   }
   while (fgets(line, 200, j) != NULL) {
      ret = strstr(line, key);
      if (ret) {
         printf("%s", line);
      }
   }
   fclose(j);
}

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   char* tString = "key:value";
   int index = 0;
   for (int i = 0; i < strlen(tString); i++)
   {
      if (tString[i] == ':')
      {
         index = i;
         break;
      }
   }

   char* tValue = &tString[index + 1];
   printf("%s\n", tValue);


}

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
   char* tString = "key:va&lue";
   char tPacked[200];
   int index = 0;
   for (int i = 0; i < strlen(tString); i++)
   {
      char c = tString[i];
      if (c != ':' && c != '&')
      {
         tPacked[index] = c;
         index++;
      }
   }
   tPacked[index] = 0;

   printf("%s\n", tPacked);


}

