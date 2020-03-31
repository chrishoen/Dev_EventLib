#pragma once

#include "risCmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

class CmdLineExec : public Ris::BaseCmdLineExec
{
public:

  CmdLineExec();

  void reset();
  void execute(Ris::CmdLineCmd* aCmd);

  void executeValueA  (Ris::CmdLineCmd* aCmd);
  void executeDeltaA  (Ris::CmdLineCmd* aCmd);
  void executeValueB  (Ris::CmdLineCmd* aCmd);
  void executeDeltaB  (Ris::CmdLineCmd* aCmd);
  void executeNoise   (Ris::CmdLineCmd* aCmd);
  void executeGo1     (Ris::CmdLineCmd* aCmd);
  void executeGo2     (Ris::CmdLineCmd* aCmd);
  void executeGo3     (Ris::CmdLineCmd* aCmd);

  void executeParms   (Ris::CmdLineCmd* aCmd);


  void executeReqA(Ris::CmdLineCmd* aCmd);
  void executeReqB(Ris::CmdLineCmd* aCmd);



};

//******************************************************************************
//******************************************************************************
//******************************************************************************

