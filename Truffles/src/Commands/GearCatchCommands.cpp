//
// Created by Jason Markham on 2/14/17.
//

#include "GearCatchCommands.h"

GearCatchCommand::GearCatchCommand(const std::string &name) : frc::Command(name) {}

void GearCatchCommand::Interrupted() {
    End();
}

//TODO: still pretty hackey
void GearCatchCommand::End() {
    Robot::gearCatch->moveInward();
}

bool GearCatchCommand::IsFinished() {
    return IsCanceled() || IsTimedOut();
}

void GearCatchCommand::Initialize() {
    Robot::gearCatch->moveOutward();
    //RobotMap::gearCatchActuator1->Set(0.615);
}


GearCatchVertical::GearCatchVertical() : GearCatchCommand("Gear Catch -> Vertical") {
    //SetTimeout(2.0); //TODO: uncomment?
    //TODO: move to common constructor?
    Requires(Robot::gearCatch.get());
}

GearCatchOut::GearCatchOut() : GearCatchCommand("Gear Catch -> Out") {
    Requires(Robot::gearCatch.get());
    //SetTimeout(2.0);
}

GearCatchIn::GearCatchIn() : GearCatchCommand("Gear Catch -> In") {
    Requires(Robot::gearCatch.get());
}

void GearCatchVertical::Execute() {
    Robot::gearCatch->moveVertical();
}


void GearCatchOut::Execute() {
    Robot::gearCatch->moveOutward();
}

void GearCatchIn::Execute() {
    double prevPosition = Robot::gearCatch->getPosition();
    double nextPosition = prevPosition - 0.01;
    if (nextPosition > 0.0001) {
        Robot::gearCatch->setPosition(nextPosition);

    } else {
        Robot::gearCatch->setPosition(0.0);
        Cancel();
    }

    SmartDashboard::PutNumber("gear actuator position", nextPosition);
}

