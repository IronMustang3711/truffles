#ifndef RotateOnce_H
#define RotateOnce_H

#include "WPILib.h"

class RotatWheelseOnce: public Command {
public:
	RotatWheelseOnce();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void doUpdate();
	double getPosition();

private:
	Notifier notifier{&RotatWheelseOnce::doUpdate,this};
	double initialEncoderPosition = 0;

};

#endif  // RotateOnce_H
