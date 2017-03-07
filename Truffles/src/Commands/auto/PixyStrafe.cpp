/*
 * PixyStrafe.cpp
 *
 *  Created on: 6 Mar 2017
 *      Author: steffen
 */

#include <Commands/auto/PixyStrafe.h>

PixyStrafe::PixyStrafe(): PixyCommand() {
}

void PixyStrafe::Execute() {
	PixyCommand::Execute();
}

bool PixyStrafe::IsFinished() {
	return this->strafe == PixyMovement::NONE;
}

PixyStrafe::~PixyStrafe() {
}
