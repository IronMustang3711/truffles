/*
 * StrafeCommand.cpp
 *
 *  Created on: Mar 6, 2017
 *      Author: jason
 */

#include <Commands/auto/StrafeCommand.h>

StrafeCommand::StrafeCommand() :Command("strafe") {
	//Requires(Robot::chassis);
SetTimeout(2.0);
}
bool StrafeCommand::IsFinished() {
	return !IsTimedOut();
}

