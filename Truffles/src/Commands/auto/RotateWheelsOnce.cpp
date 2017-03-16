#include <Commands/auto/RotateWheelsOnce.h>
#include "../../Robot.h"

RotateWheelseOnce::RotateWheelseOnce() :  Command("rotate wheels 1x") {
}

void RotateWheelseOnce::Initialize() {
	Robot::chassis->zeroEncoders();
	initialEncoderPosition = getPosition();

}

void RotateWheelseOnce::Execute() {

}

bool RotateWheelseOnce::IsFinished() {
	return IsTimedOut() || IsCanceled()
			|| (getPosition() - initialEncoderPosition) >= 1.0;
}

void RotateWheelseOnce::End() {
	Robot::chassis->stop();

}

void RotateWheelseOnce::doUpdate() {
	if (!IsFinished()) {
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
