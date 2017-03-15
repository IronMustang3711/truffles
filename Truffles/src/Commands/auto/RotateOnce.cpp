#include "RotateOnce.h"

RotateOnce::RotateOnce() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void RotateOnce::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void RotateOnce::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool RotateOnce::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void RotateOnce::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RotateOnce::Interrupted() {

}
