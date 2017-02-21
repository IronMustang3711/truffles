//
// Created by Jason Markham on 2/14/17.
//

#ifndef TRUFFLES_GEARCATCHCOMMANDS_H
#define TRUFFLES_GEARCATCHCOMMANDS_H

#include "../Robot.h"
#include <Commands/Command.h>

class GearCatchCommand : public frc::Command {
 public:
  GearCatchCommand(const std::string& name);
  virtual void Interrupted() override;

  virtual void End() override;

  virtual bool IsFinished() override;

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

  virtual void Interrupted() override;

  virtual void End() override;

  virtual bool IsFinished() override;

  virtual void Initialize() override;

  virtual void Execute() override;

 private:
  GearCatchIn catchIn{};
  GearCatchOut catchOut{};
  // GearCatchChill chill{};
  Command* currentCommand;
};
#endif  // TRUFFLES_GEARCATCHCOMMANDS_H
