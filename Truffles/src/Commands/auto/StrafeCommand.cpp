/*
 * StrafeCommand.cpp
 *
 *  Created on: Mar 6, 2017
 *      Author: jason
 */

#include "StrafeCommand.h"
#include "../../Robot.h"
double sgn(double in) {
	return in > 0 ? 1 : in == 0 ? 0 : -1;
}
StrafeCommand::StrafeCommand(double distance) :
		Command("strafe"), timer { }, targetDistance(distance) {
	updater = std::make_unique<Notifier>(&StrafeCommand::Execute, this);
	drive = Robot::chassis;
	Requires(Robot::chassis.get());
	SetTimeout(4.0);
}
bool StrafeCommand::IsFinished() {
	return IsTimedOut();
}
void StrafeCommand::Initialize() {
	initialHeading = drive->getHeading();
	timer.Reset();
	timer.Start();
	updater->StartPeriodic(0.01);

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
	drive->MecanumDrive_Cartesian(sgn(targetDistance) * 0.8, 0, 0,
			0.05 * heading);
}

void StrafeCommand::End() {
	drive->Drive(0, 0);
	updater->Stop();
	timer.Stop();
}
