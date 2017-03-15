//
// Created by Jason Markham on 3/3/17.
//

#ifndef TRUFFLES_DRIVESTRAIGHT_H
#define TRUFFLES_DRIVESTRAIGHT_H
#include <WPILib.h>
class DriveStraight: public Command, PIDSource, PIDOutput {
public:
	DriveStraight(double distanceInInches);

	virtual ~DriveStraight();
	double encoderValue();

	virtual void Initialize() override;
	virtual void Execute() override;
	virtual void End() override;
	virtual bool IsFinished() override;

// PIDOutput interface
	virtual void PIDWrite(double output);

	// PIDSource interface
	virtual double PIDGet();

private:
	double targetDistance = 0;
	double initialHeading = 0;
	double initialEncoder = 0;
	PIDController pid;


};

#endif  // TRUFFLES_DRIVESTRAIGHT_H
