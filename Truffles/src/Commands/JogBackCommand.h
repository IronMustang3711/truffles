#ifndef JogBackCommand_H
#define JogBackCommand_H

#include "WPILib.h"

class JogBackCommand: public Command, PIDSource, PIDOutput {
public:
	JogBackCommand();
	void Initialize() override;
	void Execute() override;
	void End() override;
	bool IsFinished() override;

	double encoderValue();

	// PIDOutput interface
	virtual void PIDWrite(double output) override;

	// PIDSource interface
	virtual double PIDGet() override;
private:
	double targetRotations = 0;
	double initialEncoder = 0;
	PIDController pid;

};

#endif  // JogBackCommand_H
