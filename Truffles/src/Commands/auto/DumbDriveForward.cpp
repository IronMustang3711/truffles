#include "DumbDriveForward.h"
#include "../../Robot.h"
DumbDriveForward::DumbDriveForward() : TimedCommand("drive forward(timed)",5.0) {
	  Requires(Robot::chassis.get());
}



// Called repeatedly when this Command is scheduled to run
void DumbDriveForward::Execute() {
	Robot::chassis->AutoDrive(0.3,0.0);

}

// Called once after command times out
void DumbDriveForward::End() {
	Robot::chassis->stop();

}


