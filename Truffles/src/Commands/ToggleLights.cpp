//
// Created by Jason Markham on 2/20/17.
//

#include "ToggleLights.h"

void ToggleLights::Execute() {
	RobotMap::lightsRed->Set(!RobotMap::lightsRed->Get());
	RobotMap::lightsGreen->Set(!RobotMap::lightsGreen->Get());
	RobotMap::lightsBlue->Set(!RobotMap::lightsBlue->Get());
}

ToggleLights::ToggleLights() :
		InstantCommand() {
}
