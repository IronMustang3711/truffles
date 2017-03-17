#ifndef DRIVEWITHJOYSTICK_H
#define DRIVEWITHJOYSTICK_H

#include "../Robot.h"
#include "Commands/Subsystem.h"

class DriveWithJoystick: public Command {
public:
	DriveWithJoystick();

private:
	virtual void Execute() override;
	virtual bool IsFinished() override;
	virtual void Interrupted() override;
	virtual void End() override;
};

#endif
