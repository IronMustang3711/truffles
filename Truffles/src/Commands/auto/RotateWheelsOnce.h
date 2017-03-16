#ifndef RotateOnce_H
#define RotateOnce_H

#include "WPILib.h"

class RotateWheelseOnce: public Command {
public:
	RotateWheelseOnce();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void doUpdate();
	double getPosition();
	double error();

private:
	Notifier notifier{&RotateWheelseOnce::doUpdate,this};
	double initialEncoderPosition = 0;

};

#endif  // RotateOnce_H
