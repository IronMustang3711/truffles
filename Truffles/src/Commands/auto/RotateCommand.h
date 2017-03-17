#ifndef RotateCommand_H
#define RotateCommand_H

#include "../SimpleCommand.h"
#include "../../Subsystems/Chassis.h"
#include <memory>
#include "Notifier.h"
#include "Timer.h"

class RotateCommand: public PIDCommand {
public:
	RotateCommand(double amtInDegrees);
	void Initialize() override;
	void Execute() override;
	void End() override;
    bool IsFinished() override;

	virtual double ReturnPIDInput() override;
	virtual void UsePIDOutput(double output) override;

private:
	double startAngle = 0;
	double dstAngle = 0;
};

#endif  // RotateCommand_H
