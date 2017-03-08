#include "RotateCommand.h"
#include "../../Robot.h"
#include <string>
std::string PIDTypeName(PIDSourceType type) {
  switch (type) {
    case PIDSourceType::kDisplacement:
      return "Displacement";
    case PIDSourceType::kRate:
      return "Rate";
    default:
      return "butts";
  }
}

// p,i,d,f, update rate(seconds)
RotateCommand::RotateCommand() : PIDCommand("Rotate", 1, 0, 0, 0.1, 0.01) {
  Requires(Robot::chassis.get());
  SetTimeout(3.0);
  SetPIDSourceType(PIDSourceType::kDisplacement);
  SmartDashboard::PutString("gyro pid source type",
                            PIDTypeName(RobotMap::ahrs->GetPIDSourceType()));
}

void RotateCommand::Initialize() {
  startAngle = Robot::chassis->getHeading();  // or calibrate?
  dstAngle = SmartDashboard::PutNumber("rotate angle", startAngle);
  SetSetpoint(dstAngle);
}

void RotateCommand::Execute() {}

bool RotateCommand::IsFinished() {
  return IsTimedOut() || IsCanceled() ||
         std::abs(ReturnPIDInput() - GetSetpoint()) < 5.0;
}

void RotateCommand::End() {
  // TODO Pizza hut here?
}

double RotateCommand::ReturnPIDInput() {
  return Robot::chassis->getHeading();
  // return RobotMap::ahrs->PIDGet();//LOL IMPLEMENTS PIDSource but marks api as
  // private ?????!!!!
}

void RotateCommand::UsePIDOutput(double out) {
  Robot::chassis->MecanumDrive_Cartesian(0, 0, out, startAngle);
}
