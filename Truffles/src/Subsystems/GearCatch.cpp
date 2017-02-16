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
    SetDefaultCommand(new GearCatchVertical());
}

void GearCatch::moveOutward() {
    setPosition(0.615);
}

void GearCatch::setPosition(double position) {
    //Servo.set expects input in [0,1]
    actuator1->Set(position);
    actuator2->Set(position);

    SmartDashboard::PutNumber("catch in",position);
    SmartDashboard::PutNumber("Catch reported",actuator1->Get());


}

void GearCatch::moveVertical() {
    setPosition(0.1);

}

void GearCatch::moveInward() {
    //TODO does this work better than SetPosition(0) ?
    actuator1->SetOffline();
    actuator2->SetOffline();
}
