/*
 * StrafeCommand.cpp
 *
 *  Created on: Mar 6, 2017
 *      Author: jason
 */

#include "StrafeCommand.h"
#include "../../Robot.h"
StrafeCommand::StrafeCommand(double distance) : Command("strafe"), timer{},targetDistance(distance) {
  updater = std::make_unique<Notifier>(&StrafeCommand::Execute, this);
  drive = Robot::chassis;
  Requires(Robot::chassis.get());
  SetTimeout(2.0);
}
bool StrafeCommand::IsFinished() {
  return IsTimedOut();
}
void StrafeCommand::Initialize() {
  timer.Reset();
  timer.Start();
  updater->StartPeriodic(0.01);
  initialHeading = drive->getHeading();
}
void StrafeCommand::Execute() {
  // double out=0;
  //	double t = timer.Get();
  //	if(t>=0.5){
  //		rampUp=false;
  //		timer.Reset();
  //		t=0;
  //	}
  //	if(rampUp){
  //		out = 0.5*t;
  //	} else {
  //		out = 1 - 0.5*t;
  //	}
  // SmartDashboard::PutNumber("strafe out",out);
  double heading = drive->getHeading() - initialHeading;
  // if(heading<0.5) heading = 0;
  drive->MecanumDrive_Cartesian(0.8, 0, 0, heading);
}

void StrafeCommand::End() {
  drive->Drive(0, 0);
  updater->Stop();
}
