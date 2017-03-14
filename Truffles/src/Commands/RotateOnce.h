#ifndef RotateOnce_H
#define RotateOnce_H

#include "Commands/Command.h"

class RotateOnce : public Command {
public:
	RotateOnce();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // RotateOnce_H
