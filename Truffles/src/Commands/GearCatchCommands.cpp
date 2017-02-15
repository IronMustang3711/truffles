//
// Created by Jason Markham on 2/14/17.
//

#include "GearCatchCommands.h"

GearCatchVertical::GearCatchVertical() : Command("Gear Catch -> Vertical") {
    Requires(Robot::gearCatch.get());
}

GearCatchOut::GearCatchOut() : Command("Gear Catch -> Out") {
    Requires(Robot::gearCatch.get());
}

GearCatchIn::GearCatchIn() : Command("Gear Catch -> In") {
    Requires(Robot::gearCatch.get());
}

void GearCatchVertical::Execute() {
    Robot::gearCatch->moveVertical();
}

void GearCatchVertical::Interrupted() {
   End();
}

void GearCatchVertical::End() {
    Command::End();
}

bool GearCatchVertical::IsFinished() {
    return !IsTimedOut();
}

void GearCatchVertical::Initialize() {}


void GearCatchOut::Execute() {
    Robot::gearCatch->moveOutward();
}

void GearCatchOut::Initialize() {}

bool GearCatchOut::IsFinished() {
    return false;
}

void GearCatchOut::End() {}

void GearCatchOut::Interrupted() {
    End();
}

void GearCatchIn::Execute() {
    Robot::gearCatch->moveInward();
}

void GearCatchIn::Interrupted() {

}

void GearCatchIn::End() {
}

bool GearCatchIn::IsFinished() {
    return false;
}

void GearCatchIn::Initialize() {
}
