/*
 * StrafeCommand.cpp
 *
 *  Created on: Mar 6, 2017
 *      Author: jason
 */

#include "StrafeCommand.h"
#include "../../Robot.h"

StrafeCommand::StrafeCommand() :Command("strafe"),timer{} {
	Requires(Robot::chassis.get());
	SetTimeout(2.0);
}
bool StrafeCommand::IsFinished() {
	return !IsTimedOut();
}
void StrafeCommand::Initialize(){
	timer.Reset();
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


	}
}

void StrafeCommand::End() {
}
