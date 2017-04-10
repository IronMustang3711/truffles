#include "PlaceGear.h"
#include "DriverStation.h"
#include "../../Robot.h"
#include "../../vision/Vision.h"
#include <cmath>
PlaceGear::PlaceGear() :
		Command("place gear",/*timeout=*/4.0),
		targetRotations(40.0 / 18.0),
		pid { Preferences::GetInstance()->GetDouble("StraightP",0.15),
			  0,
			  Preferences::GetInstance()->GetDouble("StraightD", 0),
			  Preferences::GetInstance()->GetDouble("StraightF", 0.01),
				this,
				this, 0.02 }
{
		Requires(Robot::chassis.get());
}

double PlaceGear::encoderValue() {
	return (Robot::chassis->getLeftRearPosition());
	//+ Robot::chassis->getRightRearPosition()) / 2;
}

void PlaceGear::Initialize() {
	Robot::chassis->zeroEncoders();
	initialEncoder = Robot::chassis->getLeftRearPosition();
	pid.SetInputRange(0, targetRotations);
	pid.SetOutputRange(-0.3, 0.3);
	pid.SetAbsoluteTolerance(0.1);
	pid.SetSetpoint(targetRotations);
	initialHeading = Robot::chassis->getHeading();
	pid.Enable();
}
void PlaceGear::Execute() {
	//SmartDashboard::PutNumber("PlaceGear: error", pid.GetError());
}
void PlaceGear::End() {
	pid.Disable();
	Robot::chassis->stop();
	//	SmartDashboard::PutNumber("final position(left)",
	//			Robot::chassis->getLeftRearPosition());
	//	SmartDashboard::PutNumber("final position(right)",
	//			Robot::chassis->getRightRearPosition());
}
bool PlaceGear::IsFinished() {
	return pid.OnTarget() || IsTimedOut();
}

// PIDOutput interface
void PlaceGear::PIDWrite(double output) {
	double rotate = 0;//std::min(0.3,Vision::getInstance().PIDGet() / 50); //TODO normalize properly, in PIDGet()
	Robot::chassis->AutoDrive(output, rotate );
}

// PIDSource interface
double PlaceGear::PIDGet() {
	return encoderValue() - initialEncoder;
}

PlaceGear::~PlaceGear() {
}
