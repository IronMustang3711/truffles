#ifndef RotateCommand_H
#define RotateCommand_H

#include "../SimpleCommand.h"
#include "../../Subsystems/Chassis.h"
#include <memory>
#include "Notifier.h"
#include "Timer.h"


class RotateCommand : public PIDCommand {
public:
	RotateCommand();
	void Initialize();
	void Execute();
	void End();
	bool IsFinished() override;

	  virtual double ReturnPIDInput();
	  virtual void UsePIDOutput(double output);

private:
	double startAngle=0;
	double dstAngle=0;
};

#endif  // RotateCommand_H
