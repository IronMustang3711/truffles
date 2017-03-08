
#include "Winch.h"
#include "../RobotMap.h"

Winch::Winch() : Subsystem("Winch") {
  winchMotor = RobotMap::winchController;
}

void Winch::InitDefaultCommand() {}

void Winch::runWinchMotor(double speed) {
  //	if (speed != 0)
  //		shooterRunnng = true;
  //	else shooterRunning = false;

  winchMotor->Set(-speed);
}
