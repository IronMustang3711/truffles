#include "ReloadChoosers.h"
#include "../Robot.h"
#include "../vision/Vision.h"
ReloadChoosers::ReloadChoosers() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}



// Called repeatedly when this Command is scheduled to run
void ReloadChoosers::Execute() {
	SmartDashboard::PutData("auto modes",&(Robot::robot->chooser));
	frc::SmartDashboard::PutData("vision alg",&(Vision::getInstance().algChooser));
}

