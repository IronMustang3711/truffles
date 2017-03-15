#include "Ringlights.h"
#include "../Robot.h"
Ringlights::Ringlights() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called repeatedly when this Command is scheduled to run
void Ringlights::Execute() {
	Robot::lights->rearRinglight.toggle();
	Robot::lights->pixyRingLight.toggle();
}

