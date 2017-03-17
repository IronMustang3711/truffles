#ifndef DumbDriveForward_H
#define DumbDriveForward_H

#include "Commands/TimedCommand.h"

class SimpleDriveForward : public TimedCommand {
public:
	SimpleDriveForward();
	void Execute() override;
	void End() override;

};

#endif  // DumbDriveForward_H
