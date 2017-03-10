#ifndef PixySubsystem_H
#define PixySubsystem_H

#include <Commands/Subsystem.h>
#include "../Pixy.h"
#include <Notifier.h>

class PixySubsystem : public Subsystem {
private:
	Pixy* pixy;
	void doUpdate();
	Notifier notifier;
	int objectCount=0;
	bool enabled = false;

public:
	PixySubsystem();
	void InitDefaultCommand();
	bool isTracking();
	void enable();
	void disable();
	bool isEnabled();

	double getDistanceFromCenter();
	bool pixyCanSeeBothStrips();

	double getBlockRatio();

	std::shared_ptr<PIDSource> createPIDSourceForRotation();
	std::shared_ptr<PIDSource> createPIDSourceForStrafing();
};

#endif  // PixySubsystem_H
