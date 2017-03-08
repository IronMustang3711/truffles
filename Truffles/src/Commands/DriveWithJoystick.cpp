

#include "DriveWithJoystick.h"

DriveWithJoystick::DriveWithJoystick() : Command() {
  Requires(Robot::chassis.get());
}

void DriveWithJoystick::Execute() {
  Robot::chassis->MecanumDrive(Robot::oi->driverJoystick);
}

bool DriveWithJoystick::IsFinished() {
  return false;
}
