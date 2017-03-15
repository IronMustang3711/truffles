#ifndef RotateOnce_H
#define RotateOnce_H

#include "WPILib.h"

class RotateOnce: public Command {
public:
	RotateOnce();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void doUpdate();

private:
	Notifier notifier{&RotateOnce::doUpdate,this};
	double initialEncoderPosition = 0;
};

#endif  // RotateOnce_H
