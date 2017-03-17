//
// Created by Jason Markham on 2/14/17.
//

#include "GearCatch.h"
#include "../Commands/GearCatchCommands.h"
#include "../RobotMap.h"
/**
 * @see
 https://www.chiefdelphi.com/forums/showthread.php?t=154631&highlight=linear+actuator+servo
 *
 * @see LinearActuator
 */
GearCatch::GearCatch() :
		Subsystem("Gear Catch") {
//	actuator1 = RobotMap::gearCatchActuator1;
//	actuator2 = RobotMap::gearCatchActuator2;
}

void GearCatch::moveOut() {
	setPosition(0.615);
}

void GearCatch::setPosition(double position) {
//	actuator1->Set(position);
//	actuator2->Set(position);
}

void GearCatch::moveIn() {
	setPosition(0);
}
void GearCatch::chill() {
//	actuator1->SetOffline();
//	actuator2->SetOffline();
}

double GearCatch::getPosition() {
	return 0;
//	return actuator1->Get();
}
