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
    return false;
}

void GearCatchCommand::Initialize() {
     Requires(Robot::gearCatch.get());
}


GearCatchVertical::GearCatchVertical() : GearCatchCommand("Gear Catch -> Vertical") {
    SetTimeout(1.0);
}

GearCatchOut::GearCatchOut() : GearCatchCommand("Gear Catch -> Out") {
}

GearCatchIn::GearCatchIn() : GearCatchCommand("Gear Catch -> In") {
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
