#ifndef DumbDriveForward_H
#define DumbDriveForward_H

#include "Commands/TimedCommand.h"

class DumbDriveForward : public TimedCommand {
public:
	DumbDriveForward();
	void Execute() override;
	void End() override;

};

#endif  // DumbDriveForward_H
