#ifndef PlaceGear_H
#define PlaceGear_H

#include "WPILib.h"
/**
 * this is where we will use vision to go forward/servo axially in an attempt to place a gear.
 */
class PlaceGear : public Command {
public:
	PlaceGear();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
};

#endif  // PlaceGear_H
