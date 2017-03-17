#include "RotateCommand.h"
#include "../../Robot.h"
/*
 * Example: ~/wpilib/user/cpp/examples/navXMXP_CPP_RotateToAngle/src/Robot.cpp
 */
// positive values will rotate clockwise
// p,i,d,f, update rate(seconds)
RotateCommand::RotateCommand(double amt) :
		PIDCommand("Rotate", 0.5, 0, 0, 0.1, 0.05), dstAngle(amt) {
	Requires(Robot::chassis.get());
	SetTimeout(1.0); //TODO <-- tune
	SetPIDSourceType(PIDSourceType::kDisplacement);
	auto c = GetPIDController();
	c->SetAbsoluteTolerance(2.0);
	c->SetToleranceBuffer(3);
	c->SetInputRange(-180, 180);
	c->SetOutputRange(-0.4, 0.4);
	c->SetContinuous(true);

}

void RotateCommand::Initialize() {
	startAngle = Robot::chassis->getHeading();  // or calibrate?
	SetSetpoint(dstAngle);
}

void RotateCommand::Execute() {
}

bool RotateCommand::IsFinished() {
	return IsTimedOut() || IsCanceled() || GetPIDController()->OnTarget();
}

void RotateCommand::End() {
	Robot::chassis->stop();
}

double RotateCommand::ReturnPIDInput() {
	return Robot::chassis->getHeading() - startAngle;
}

void RotateCommand::UsePIDOutput(double out) {
	Robot::chassis->MecanumDrive_Cartesian(0, 0, out, Robot::chassis->getHeading()); //TODO instead of getHeading, try "0"
}
