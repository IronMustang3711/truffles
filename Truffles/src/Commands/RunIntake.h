
#ifndef RUNINTAKE_H
#define RUNINTAKE_H

#include <Commands/Command.h>

class RunIntake : public frc::Command {
 public:
  RunIntake();

  virtual void Initialize();
  virtual void Execute();
  virtual bool IsFinished();
  virtual void End();
  virtual void Interrupted();

  RunIntake(double speed);

 private:
  double m_speed;
};

#endif
