
#ifndef AUTONOMOUS_COMMAND_H
#define AUTONOMOUS_COMMAND_H

#include <Commands/Command.h>

class AutonomousCommand : public Command {
 public:
  AutonomousCommand();

  virtual void Initialize() override;
  virtual void Execute() override;
  virtual bool IsFinished() override;
  virtual void End() override;
  virtual void Interrupted() override;
};

#endif
