
#include "Intake.h"
#include "../RobotMap.h"
Intake::Intake() : Subsystem("Intake") {
  intakeMotor = RobotMap::intakeController;
}

void Intake::InitDefaultCommand() {}

/**
 * @value [-1,1]
 */
void Intake::run(double value) {
  intakeMotor->Set(value);
}
