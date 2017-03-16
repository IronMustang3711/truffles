#include "RotatWheelseOnce.h"
#include "../../Robot.h"

RotatWheelseOnce::RotatWheelseOnce() {
}

void RotatWheelseOnce::Initialize() {
	Robot::chassis->zeroEncoders();
	initialEncoderPosition = getPosition();

}

void RotatWheelseOnce::Execute() {

}

bool RotatWheelseOnce::IsFinished() {
	return IsTimedOut() || IsCanceled()
			|| (getPosition() - initialEncoderPosition) >= 1.0;
}

void RotatWheelseOnce::End() {
	Robot::chassis->stop();

}

void RotatWheelseOnce::doUpdate() {
	if (!IsFinished()) {
		Robot::chassis->AutoDrive(0.2, 0);
	} else{
		Robot::chassis->stop();
		Cancel();
	}
}

double RotatWheelseOnce::getPosition() {
	return (Robot::chassis->getLeftRearPosition()
			+ Robot::chassis->getRightRearPosition());
}
