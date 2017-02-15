//
// Created by Jason Markham on 2/14/17.
//

#include "GearCatch.h"
#include "../RobotMap.h"
GearCatch::GearCatch() : Subsystem("Gear Catch") {
    actuator1 = RobotMap::gearCatchActuator1;
    actuator2 = RobotMap::gearCatchActuator2;
}

void GearCatch::InitDefaultCommand() {
   //TODO: default command
}

void GearCatch::moveOutward() {
    setPosition(0.5);
}

void GearCatch::setPosition(double position) {
    actuator1->SetPosition(position);
    actuator2->SetPosition(position);

}

void GearCatch::moveVertical() {
    setPosition(0.0);

}

void GearCatch::moveInward() {
    setPosition(-0.5);

}
