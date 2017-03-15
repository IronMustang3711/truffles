//
// Created by Jason Markham on 2/21/17.
//

#include "ToggleRobotFront.h"

void ToggleRobotFront::Execute() {
	Robot::chassis->toggleRobotFrontDirection();
}
