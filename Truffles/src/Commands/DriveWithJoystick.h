#ifndef DRIVEWITHJOYSTICK_H
#define DRIVEWITHJOYSTICK_H

#include "../Robot.h"
#include "Commands/Subsystem.h"

class DriveWithJoystick: public Command {
public:
	DriveWithJoystick();

	virtual void Execute() override;
	virtual bool IsFinished() override;
};

#endif
