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
	return objectCount > 0;
}

void PixySubsystem::enable() {
	enabled = true;
	notifier.StartPeriodic(0.04); // 25 updates/sec
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
	objectCount = pixy->getBlocks();

	 int firstBlockIndex = -1;
	  int secondBlockIndex = -1;

	  if (objectCount == 2) {
	    // We assume that the two objects found are the two strips of tape
	    firstBlockIndex = 0;
	    secondBlockIndex = 1;
	  } else if (objectCount > 2) {
	    // There's some kind of interference or other objects found, so attempt to
	    // find the find ones
	    for (int i = 0; i < objectCount; i++) {
	      double objectAspect =
	          RobotMap::pixy->blocks[i].height / RobotMap::pixy->blocks[i].width;

	      // Ideal aspect is 10/2.5=4, but let's be flexible to handle looking at it
	      // from the side/rotated etc
	      if ((objectAspect >= 2) && (objectAspect <= 4)) {
	        if (firstBlockIndex == -1) {
	          firstBlockIndex = i;
	        } else {
	          secondBlockIndex = i;
	        }
	      }
	    }
	  }
}

std::shared_ptr<PIDSource> PixySubsystem::createPIDSourceForRotation() {
	return std::make_shared<utils::PIDSourceAdapter>(std::bind(&PixySubsystem::getDistanceFromCenter,this));
}

std::shared_ptr<PIDSource> PixySubsystem::createPIDSourceForStrafing() {
	return std::make_shared<utils::PIDSourceAdapter>(std::bind(&PixySubsystem::getBlockRatio,this));
}

