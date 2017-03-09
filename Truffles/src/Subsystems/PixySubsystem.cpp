#include "PixySubsystem.h"
#include "../RobotMap.h"
#include "../PIDStuff.h"

PixySubsystem::PixySubsystem() : Subsystem("ExampleSubsystem"),
pixy{RobotMap::pixy},
notifier{&PixySubsystem::doUpdate,this}
{
	enable();

}

void PixySubsystem::InitDefaultCommand() {

}

bool PixySubsystem::isTracking() {
	return numberOfTracks > 0;
}

void PixySubsystem::enable() {
	enabled = true;
	notifier.StartPeriodic(0.03); // 30 updates/sec
}

void PixySubsystem::disable() {
	enabled = false;
	notifier.Stop();
}

bool PixySubsystem::isEnabled() {
	return enabled;
}

double PixySubsystem::getDistanceFromCenter() {
	return -1;
}

bool PixySubsystem::pixyCanSeeBothStrips() {
	return false;
}

double PixySubsystem::getBlockRatio() {
	return -1;
}

void PixySubsystem::doUpdate() {
	numberOfTracks = pixy->getBlocks();
}

std::shared_ptr<PIDSource> PixySubsystem::createPIDSourceForRotation() {
	return std::make_shared<utils::PIDSourceAdapter>(std::bind(&PixySubsystem::getDistanceFromCenter,this));
}

std::shared_ptr<PIDSource> PixySubsystem::createPIDSourceForStrafing() {
	return std::make_shared<utils::PIDSourceAdapter>(std::bind(&PixySubsystem::getBlockRatio,this));
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
