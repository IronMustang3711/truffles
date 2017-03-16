#include <Commands/auto/RotateWheelsOnce.h>
#include "../../Robot.h"
#include <iostream>
RotateWheelseOnce::RotateWheelseOnce() :  Command("rotate wheels 1x") {
}

void RotateWheelseOnce::Initialize() {
	Robot::chassis->zeroEncoders();
	initialEncoderPosition = getPosition();
	notifier.StartPeriodic(0.02);

}

void RotateWheelseOnce::Execute() {

}

bool RotateWheelseOnce::IsFinished() {
	return IsTimedOut() || IsCanceled()|| error() < 0.1;
}

void RotateWheelseOnce::End() {
	Robot::chassis->stop();

}

void RotateWheelseOnce::doUpdate() {
	if (!IsFinished()) {
		std::cout << "err: "<< error() <<std::endl;
		Robot::chassis->AutoDrive(0.2, 0);
	} else{
		Robot::chassis->stop();
		Cancel();
	}
}

double RotateWheelseOnce::getPosition() {
	return (Robot::chassis->getLeftRearPosition()
			+ Robot::chassis->getRightRearPosition());
}

double RotateWheelseOnce::error() {
	return 1 - getPosition()-initialEncoderPosition;
}
