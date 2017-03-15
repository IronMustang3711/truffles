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
			Command("drive straight(simple)"), targetDistance(19*distanceInInches)
			//p,i,d,f,src,target,update rate
					, pid { 0.01, 0, 0, 0.001, this, this, 0.02 } {

	}

	virtual ~SimpleDriveStraight() {
	}

	virtual void Initialize() override {
		timer.Reset();
		timer.Start();
		pid.SetInputRange(0, targetDistance);
		pid.SetOutputRange(-0.3, 0.3);
		pid.SetPercentTolerance(1);
		initialHeading = Robot::chassis->getHeading();
		pid.Enable();
		// notifier.StartPeriodic(0.02); //50 hz
	}
	virtual void Execute() override {
	}
	virtual void End() override {
		timer.Stop();
		timer.Reset();
		pid.Disable();
		SmartDashboard::PutNumber("final position(left)",
				Robot::chassis->getLeftRearPosition());
		SmartDashboard::PutNumber("final position(right)",
				Robot::chassis->getRightRearPosition());
	}
	virtual bool IsFinished() override {
		return pid.OnTarget();
	}

// PIDOutput interface
	virtual void PIDWrite(double output) {
		double headingCorrection = 0.02*(initialHeading - Robot::chassis->getHeading());
		Robot::chassis->AutoDrive(output, headingCorrection);
	}

	// PIDSource interface
	virtual double PIDGet() {
		return (Robot::chassis->getLeftRearPosition()
				+ Robot::chassis->getRightRearPosition()) / 2;
	}

private:
	double targetDistance = 0;
	double initialHeading = 0;
	PIDController pid;
	// Notifier notifier{&SimpleDriveStraight::doUpdate,this};
	Timer timer { };

};

class SimpleRotate: public Command {
public:
	SimpleRotate(double targetHeadingInDegrees_Relative) :
			Command("rotate(simple)"), targetHeading(targetHeadingInDegrees_Relative) {
	}

	virtual void Initialize() override {
		initialHeading = Robot::chassis->getHeading();
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
