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
			Command("drive straight(simple)",/*timeout=*/5.0), targetDistance(
					19 * distanceInInches)
					//p,i,d,f,src,target,update rate
							, pid { 0.01, 0, 0, 0.001, this, this, 0.02 } {

	}

	virtual ~SimpleDriveStraight() {
	}

	double encoderValue() {
		return (Robot::chassis->getLeftRearPosition()
				+ Robot::chassis->getRightRearPosition()) / 2;
	}

	virtual void Initialize() override {
		Robot::chassis->zeroEncoders();
		pid.SetInputRange(0, targetDistance);
		pid.SetOutputRange(-0.3, 0.3);
		pid.SetAbsoluteTolerance(5.0);
		initialHeading = Robot::chassis->getHeading();
		pid.Enable();
	}
	virtual void Execute() override {
	}
	virtual void End() override {
		pid.Disable();
		SmartDashboard::PutNumber("final position(left)",
				Robot::chassis->getLeftRearPosition());
		SmartDashboard::PutNumber("final position(right)",
				Robot::chassis->getRightRearPosition());
	}
	virtual bool IsFinished() override {
		return pid.OnTarget() || IsTimedOut();
	}

// PIDOutput interface
	virtual void PIDWrite(double output) {
		Robot::chassis->AutoDrive(output, 0);
	}

	// PIDSource interface
	virtual double PIDGet() {
		return encoderValue() - initialEncoder;
	}

private:
	double targetDistance = 0;
	double initialHeading = 0;
	double initialEncoder = 0;
	PIDController pid;


};

class SimpleRotate: public Command {
public:
	SimpleRotate(double targetHeadingInDegrees_Relative) :
			Command("rotate(simple)"), targetHeading(
					targetHeadingInDegrees_Relative) {
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
