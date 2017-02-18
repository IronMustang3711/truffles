//
// Created by Jason Markham on 2/14/17.
//

#include "GearCatchCommands.h"

GearCatchCommand::GearCatchCommand(const std::string &name) : frc::Command(name) {
    Requires(Robot::gearCatch.get());
}

void GearCatchCommand::Interrupted() {
    End();
}

//TODO: still pretty hackey
void GearCatchCommand::End() {
    gearCatch->chill();
}

bool GearCatchCommand::IsFinished() {
    return IsCanceled() || IsTimedOut();
}

void GearCatchCommand::Initialize() {
    gearCatch->moveOut(); //TODO see if this can be removed
}


GearCatchOut::GearCatchOut() : GearCatchCommand("Gear Catch -> Out") {
    SetTimeout(2.0);
}

GearCatchIn::GearCatchIn() : GearCatchCommand("Gear Catch -> In") {
    SetTimeout(2.0);
}

void GearCatchOut::Execute() {
    gearCatch->moveOut();
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


void GearCatchChill::Execute() {
    gearCatch->chill();
}

GearCatchChill::GearCatchChill() : GearCatchCommand("Gear Catch in (undriven)") {

}


GearCatchToggle::GearCatchToggle() : frc::Command("Gear Catch Toggle"), currentCommand(nullptr) {

}

void GearCatchToggle::Interrupted() {
    End();
}

void GearCatchToggle::End() {

}

bool GearCatchToggle::IsFinished() {
    return IsCanceled() || IsTimedOut();
}

void GearCatchToggle::Initialize() {
    Command *curr = Robot::gearCatch->GetCurrentCommand();
    if (curr != nullptr) {
        currentCommand = curr;
    }
}

void GearCatchToggle::Execute() {
    if (typeid(currentCommand) == typeid(GearCatchChill)) {
        catchOut.Start();
    } else if (typeid(currentCommand) == typeid(GearCatchIn)) {
        catchOut.Start();
    } else if (typeid(currentCommand) == typeid(GearCatchOut)) {
        catchIn.Start();
    }
}
