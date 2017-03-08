
#ifndef INTAKE_H
#define INTAKE_H

#include "Commands/Subsystem.h"
#include <SpeedController.h>

class Intake : public Subsystem {
 private:
  std::shared_ptr<SpeedController> intakeMotor;

 public:
  Intake();
  void InitDefaultCommand();
  void run(double value);
};

#endif
