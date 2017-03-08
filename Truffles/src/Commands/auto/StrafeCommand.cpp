/*
 * StrafeCommand.cpp
 *
 *  Created on: Mar 6, 2017
 *      Author: jason
 */

#include "StrafeCommand.h"
#include "../../Robot.h"
StrafeCommand::StrafeCommand() :Command("strafe"),timer{} {
	  updater = std::make_unique<Notifier>(&StrafeCommand::Execute, this);
	  drive = Robot::chassis;
	Requires(Robot::chassis.get());
	SetTimeout(2.0);

}
bool StrafeCommand::IsFinished() {
	return !IsTimedOut();
}
void StrafeCommand::Initialize(){
	timer.Reset();
	updater->StartPeriodic(0.01);
	initialHeading = drive->getHeading();
}
void StrafeCommand::Execute() {
	double out=0;
	double t = timer.Get();
	if(t>=0.5){
		rampUp=false;
		timer.Reset();
		t=0;
	}
	if(rampUp){
		out = 0.5*t;
	} else {
		out = 0.5 - 0.5*t;
	}
	drive->MecanumDrive_Cartesian(out,0,drive->getHeading()-initialHeading);

}

void StrafeCommand::End() {
	updater->Stop();
}
