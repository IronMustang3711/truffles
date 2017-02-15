//
// Created by Jason Markham on 2/14/17.
//

#include "GearCatchCommands.h"
GearCatchCommand::GearCatchCommand(const std::string &name) : frc::Command(name) {}
void GearCatchCommand::Interrupted() {
    End();
}

void GearCatchCommand::End() {}

bool GearCatchCommand::IsFinished() {
    return false;//!IsTimedOut();
}

void GearCatchCommand::Initialize() {}


GearCatchVertical::GearCatchVertical() : GearCatchCommand("Gear Catch -> Vertical") {
    Requires(Robot::gearCatch.get());
}

GearCatchOut::GearCatchOut() : GearCatchCommand("Gear Catch -> Out") {
    Requires(Robot::gearCatch.get());
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
    Robot::gearCatch->moveInward();
}
