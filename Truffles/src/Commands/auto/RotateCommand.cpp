#include "RotateCommand.h"
#include "../../Robot.h"

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
RotateCommand::RotateCommand(double amt) : PIDCommand("Rotate", 0.5, 0, 0, 0.1, 0.05),dstAngle(amt) {
  Requires(Robot::chassis.get());
  SetTimeout(3.0);
  SetPIDSourceType(PIDSourceType::kDisplacement);
  auto c = GetPIDController();
  c->SetAbsoluteTolerance(2.0);
  c->SetToleranceBuffer(3);
  c->SetInputRange(-180,180);
  c->SetOutputRange(-1,1);
  c->SetContinuous(true);


}

void RotateCommand::Initialize() {
  startAngle = Robot::chassis->getHeading();  // or calibrate?
  SetSetpoint(dstAngle);
}

void RotateCommand::Execute() {}

bool RotateCommand::IsFinished() {
  return IsTimedOut() || IsCanceled() || GetPIDController()->OnTarget();
}

void RotateCommand::End() {
 Robot::chassis->stop();
}

double RotateCommand::ReturnPIDInput() {
  return Robot::chassis->getHeading();
}

void RotateCommand::UsePIDOutput(double out) {
  Robot::chassis->MecanumDrive_Cartesian(0, 0, out, startAngle); //TODO: instead of startAngle, try Robot::chassis->getHeading()
}
