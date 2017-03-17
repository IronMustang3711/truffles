#include "DriveStraight.h"
#include "../../Robot.h"
/*
 * example: /Users/jason/repos/wpi/FRC-Examples/CPP_Pigeon_StraightServo_Example/src/Robot.cpp
 */
DriveStraight::DriveStraight(double distanceInInches) :
		Command("drive straight(simple)",/*timeout=*/4.0), targetRotations(
				 distanceInInches/20.0)
				//p,i,d,f,src,target,update rate
						, pid { 0.01, 0, 0, 0.001, this, this, 0.02 } {

}

DriveStraight::~DriveStraight() {
}

double DriveStraight::encoderValue() {
	return (Robot::chassis->getLeftRearPosition());
			//+ Robot::chassis->getRightRearPosition()) / 2;
}

 void DriveStraight::Initialize() {
	Robot::chassis->zeroEncoders();
	pid.SetInputRange(0, targetRotations);
	pid.SetOutputRange(-0.3, 0.3);
	pid.SetAbsoluteTolerance(5.0);
	initialHeading = Robot::chassis->getHeading();
	pid.Enable();
}
void DriveStraight::Execute() {
	SmartDashboard::PutNumber("DriveStraight: error",pid.GetError());
}
 void DriveStraight::End() {
	pid.Disable();
//	SmartDashboard::PutNumber("final position(left)",
//			Robot::chassis->getLeftRearPosition());
//	SmartDashboard::PutNumber("final position(right)",
//			Robot::chassis->getRightRearPosition());
}
 bool DriveStraight::IsFinished() {
	return pid.OnTarget() || IsTimedOut();
}

// PIDOutput interface
 void DriveStraight::PIDWrite(double output) {

	Robot::chassis->AutoDrive(output, 0);
}

// PIDSource interface
 double DriveStraight::PIDGet() {
	return encoderValue() - initialEncoder;
}

