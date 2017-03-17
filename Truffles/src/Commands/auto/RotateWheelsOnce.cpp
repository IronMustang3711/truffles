#include "RotateWheelsOnce.h"
#include "../../Robot.h"
#include <iostream>
//TODO:: This goes about 20"
//TODO:: This Command ruins driving after use
RotateWheelseOnce::RotateWheelseOnce() :  Command("rotate wheels 1x") {
}

void RotateWheelseOnce::Initialize() {
	Robot::chassis->zeroEncoders();
	initialEncoderPosition = getPosition();
	notifier.StartPeriodic(0.02);

}

void RotateWheelseOnce::Execute() {
	std::cout << "err: "<< error() <<std::endl;
}

bool RotateWheelseOnce::IsFinished() {
	return IsTimedOut()|| error() < 0.1;
}

void RotateWheelseOnce::End() {
	Robot::chassis->stop();

}

void RotateWheelseOnce::doUpdate() {
	if (!IsFinished()) {
		Robot::chassis->AutoDrive(0.2, 0);
	} else{
		Robot::chassis->stop();

	}
}

double RotateWheelseOnce::getPosition() {
	return Robot::chassis->getLeftRearPosition();
}

double RotateWheelseOnce::error() {
	return 1 - getPosition()-initialEncoderPosition;
}
