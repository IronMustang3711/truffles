#include "Lights.h"
#include "../RobotMap.h"

Lights::Lights() :
		Subsystem("ExampleSubsystem") {

}

void Lights::InitDefaultCommand() {

}

void Lights::setRinglightsState(bool on) {
	rearRinglight.setOn(on);
	pixyRingLight.setOn(on);
}

