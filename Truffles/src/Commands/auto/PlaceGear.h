#ifndef PlaceGear_H
#define PlaceGear_H

#include "WPILib.h"
/**
 * this is where we will use vision to go forward/servo axially in an attempt to place a gear.
 */
class PlaceGear :public Command, PIDSource, PIDOutput {
public:
	PlaceGear();

	virtual ~PlaceGear();
	double encoderValue();

	virtual void Initialize() override;
	virtual void Execute() override;
	virtual void End() override;
	virtual bool IsFinished() override;

// PIDOutput interface
	virtual void PIDWrite(double output) override;

	// PIDSource interface
	virtual double PIDGet() override;

private:
	double targetRotations = 0;
	double initialHeading = 0;
	double initialEncoder = 0;
	PIDController pid;

};

#endif  // PlaceGear_H
