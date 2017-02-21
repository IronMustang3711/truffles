//
// Created by Jason Markham on 2/14/17.
//

#ifndef TRUFFLES_GEARCATCHCOMMANDS_H
#define TRUFFLES_GEARCATCHCOMMANDS_H

#include "../Robot.h"
#include <Commands/Command.h>

class GearCatchCommand : public InstantCommand {
 public:
  GearCatchCommand(const std::string& name);
 // virtual void Interrupted() override;

  //virtual void End() override;

  virtual void Initialize() override;

  std::shared_ptr<GearCatch> gearCatch = Robot::gearCatch;
};

class GearCatchOut : public GearCatchCommand {
 public:
  GearCatchOut();

  virtual void Execute() override;
};

class GearCatchIn : public GearCatchCommand {
 public:
  GearCatchIn();

   // bool IsFinished() override;

    virtual void Execute() override;
};

class GearCatchInUnpowered : public GearCatchCommand {
 public:
  GearCatchInUnpowered();

  virtual void Execute() override;
};

class GearCatchToggle : public Command {
 public:
  GearCatchToggle();

  virtual void End() override;

  virtual void Initialize() override;

  virtual void Execute() override;

  void setCurrentCommand(GearCatchCommand* cmd);

 protected:
  bool IsFinished() override;
  void changeCommand();

 private:
  GearCatchIn catchIn{};
  GearCatchOut catchOut{};
  GearCatchInUnpowered chill{};
  Command* currentCommand;
};
#endif  // TRUFFLES_GEARCATCHCOMMANDS_H
