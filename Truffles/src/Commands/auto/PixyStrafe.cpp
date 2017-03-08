/*
 * PixyStrafe.cpp
 *
 *  Created on: 6 Mar 2017
 *      Author: steffen
 */

#include "PixyStrafe.h"

PixyStrafe::PixyStrafe(): PixyCommand() {
}

void PixyStrafe::Execute() {
	PixyCommand::Execute();

	//Robot::chassis->AutoDrive();
	if (this->strafe == PixyMovement::LEFT) {
		Robot::chassis->MecanumDrive_Cartesian(-1, 0, 0, 0);
	} else if (this->strafe == PixyMovement::RIGHT) {
		Robot::chassis->MecanumDrive_Cartesian(1, 0, 0, 0);
	}
}

bool PixyStrafe::IsFinished() {
	return (this->strafe == PixyMovement::NONE) || IsTimedOut();
}

PixyStrafe::~PixyStrafe() {
}
