/*
 * PixyRotate.cpp
 *
 *  Created on: 6 Mar 2017
 *      Author: steffen
 */

#include "PixyRotate.h"

PixyRotate::PixyRotate() : PixyCommand() {}

void PixyRotate::Initialize() {
   PixyCommand::Initialize();
   updater = std::make_unique<Notifier>(&PixyRotate::Execute, this);
   updater->StartPeriodic(0.01);
}

void PixyRotate::Execute() {
  PixyCommand::Execute();

  if (this->rotate == PixyMovement::LEFT) {
    Robot::chassis->MecanumDrive_Cartesian(0, 0, -1.0, 0);
  } else if (this->rotate == PixyMovement::RIGHT) {
    Robot::chassis->MecanumDrive_Cartesian(0, 0, 1.0, 0);
  }
}

bool PixyRotate::IsFinished() {
  //return (this->rotate == PixyMovement::NONE) || IsTimedOut() || IsCanceled();
	return IsTimedOut();
}

PixyRotate::~PixyRotate() {}
