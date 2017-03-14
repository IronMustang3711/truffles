/*
 * SimpleAuto.cpp
 *
 *  Created on: Mar 7, 2017
 *      Author: jason
 */

#include "SimpleAuto.h"
#include <Commands/Command.h>
#include "../../Robot.h"
#include "Notifier.h"
#include "../../PIDStuff.h"

class SimpleDriveStraight: public Command, PIDSource, PIDOutput {
public:
	SimpleDriveStraight(double distanceInInches) :
			Command("drive straight(simple)"), targetDistance(distanceInInches)
			//p,i,d,f,src,target,update rate
					, pid { 0.01, 0, 0, 0.001, this, this, 0.02 } {
	}

	virtual ~SimpleDriveStraight() {
	}

	virtual void Initialize() override {
		timer.Reset();
		timer.Start();
		pid.SetInputRange(0,targetDistance);
		pid.SetOutputRange(0,0.6);
		pid.Enable();
		// notifier.StartPeriodic(0.02); //50 hz
	}
	virtual void Execute() override {
	}
	virtual void End() override {
		timer.Stop();
		timer.Reset();
		pid.Disable();
	}
	virtual bool IsFinished() override {
		return pid.OnTarget();
	}

//	void doUpdate() {
//
//	}

	// PIDOutput interface
	virtual void PIDWrite(double output){
		Robot::chassis->AutoDrive(output,0);
	}

	// PIDSource interface
	virtual double PIDGet(){
		return (Robot::chassis->getLeftFrontPosition() + Robot::chassis->getRightFrontPosition())/2;
	}

private:
	double targetDistance = 0;
	PIDController pid;
	// Notifier notifier{&SimpleDriveStraight::doUpdate,this};
	Timer timer { };

};

class SimpleRotate: public Command {
public:
	SimpleRotate(double targetHeadingInDegrees) :
			Command("rotate(simple)"), targetHeading(targetHeadingInDegrees) {
	}

	virtual void Initialize() override {
	}
	virtual void Execute() override {
	}
	virtual void End() override {
	}
	virtual bool IsFinished() override {
		return false;
	}

private:
	double initialHeading = 0;
	double targetHeading = 0;

};
