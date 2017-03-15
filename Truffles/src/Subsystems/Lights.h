#ifndef Lights_H
#define Lights_H

#include <Commands/Subsystem.h>
#include "../RobotMap.h"
class Light {
public:
	std::shared_ptr<Solenoid> impl;
	Light(std::shared_ptr<Solenoid> light) :
			impl(light) {

	}
	bool isOn() {
		return impl->Get();
	}
	void setOn(bool on) {
		impl->Set(on);
	}
	void toggle() {
		setOn(!isOn());
	}
};

class Lights: public Subsystem {

public:
	Lights();
	void InitDefaultCommand();

	Light perimeterRed = Light(RobotMap::lightsRed);
	Light perimeterGreen = Light(RobotMap::lightsGreen);
	Light perimeterBlue = Light(RobotMap::lightsBlue);

	Light rearRinglight = Light(RobotMap::rearRingLight);
	Light pixyRingLight = Light(RobotMap::pixyRinglight);
};

#endif  // Lights_H
