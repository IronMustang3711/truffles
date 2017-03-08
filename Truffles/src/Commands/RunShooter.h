
#ifndef RUNSHOOTER_H
#define RUNSHOOTER_H

#include <Commands/Command.h>
#include <Commands/CommandGroup.h>
#include <memory>

class RunShooter : public Command {
 public:
  RunShooter();

  virtual void Initialize();
  virtual void Execute();
  virtual bool IsFinished();
  virtual void End();
  virtual void Interrupted();

 private:
  bool enabled{true};
};

class RunShooterAndIntake : public CommandGroup {
 public:
  RunShooterAndIntake();
  virtual ~RunShooterAndIntake();

 private:
  Command* runShooterCommand;
  Command* runIntakeCommand;
};

#endif
