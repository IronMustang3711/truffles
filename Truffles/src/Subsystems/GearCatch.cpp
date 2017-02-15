//
// Created by Jason Markham on 2/14/17.
//

#include "GearCatch.h"
#include "../RobotMap.h"
#include "../Commands/GearCatchCommands.h"
GearCatch::GearCatch() : Subsystem("Gear Catch") {
    actuator1 = RobotMap::gearCatchActuator1;
    actuator2 = RobotMap::gearCatchActuator2;
}

void GearCatch::InitDefaultCommand() {
   //TODO: default command
	//SetDefaultCommand(new GearCatchVertical());
}

void GearCatch::moveOutward() {
    setPosition(0.6);
}

void GearCatch::setPosition(double position) {
    actuator1->Set(position);
    actuator2->Set(position);

}

void GearCatch::moveVertical() {
    setPosition(0.0);

}

void GearCatch::moveInward() {
    setPosition(-0.5);

}
