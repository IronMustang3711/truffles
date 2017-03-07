/*
 * PixyRotate.cpp
 *
 *  Created on: 6 Mar 2017
 *      Author: steffen
 */

#include <Commands/auto/PixyRotate.h>

PixyRotate::PixyRotate(): PixyCommand() {
}

void PixyRotate::Execute() {
	PixyCommand::Execute();
}

bool PixyRotate::IsFinished() {
	return this->rotate == PixyMovement::NONE;
}

PixyRotate::~PixyRotate() {
}
