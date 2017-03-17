#include "DriveStraight.h"
#include "../../Robot.h"
/*
 * example: /Users/jason/repos/wpi/FRC-Examples/CPP_Pigeon_StraightServo_Example/src/Robot.cpp
 */
DriveStraight::DriveStraight(double distanceInInches) :
		Command("drive straight",/*timeout=*/5.0), targetRotations(
				 distanceInInches/18.0)
				//p,i,d,f,src,target,update rate
						, pid { 0.15, 0, 0, 0.01, this, this, 0.02 } {
							Requires(Robot::chassis.get());

}

DriveStraight::~DriveStraight() {
}

double DriveStraight::encoderValue() {
	return (Robot::chassis->getLeftRearPosition());
			//+ Robot::chassis->getRightRearPosition()) / 2;
}

 void DriveStraight::Initialize() {
	Robot::chassis->zeroEncoders();
	initialEncoder = Robot::chassis->getLeftRearPosition();
	pid.SetInputRange(0, targetRotations);
	pid.SetOutputRange(-0.3, 0.3);
	pid.SetAbsoluteTolerance(0.1);
	pid.SetSetpoint(targetRotations);
	initialHeading = Robot::chassis->getHeading();
	pid.Enable();
}
void DriveStraight::Execute() {
	SmartDashboard::PutNumber("DriveStraight: error",pid.GetError());
}
 void DriveStraight::End() {
	pid.Disable();
	Robot::chassis->stop();
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

