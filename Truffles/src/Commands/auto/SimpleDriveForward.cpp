#include "SimpleDriveForward.h"
#include "../../Robot.h"
SimpleDriveForward::SimpleDriveForward() : TimedCommand("drive forward(timed)",4.0) {
	  Requires(Robot::chassis.get());
}



// Called repeatedly when this Command is scheduled to run
void SimpleDriveForward::Execute() {
	Robot::chassis->AutoDrive(0.3,0.0);

}

// Called once after command times out
void SimpleDriveForward::End() {
	Robot::chassis->stop();

}


