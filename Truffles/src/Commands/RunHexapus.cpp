//
// Created by Jason Markham on 2/13/17.
//

#include "RunHexapus.h"

bool RunHexapus::IsFinished() {
    return IsTimedOut();
}

void RunHexapus::Initialize() {
    Command::Initialize();
}

void RunHexapus::Execute() {
//    motorController->Set(amt);
    if (Robot::shooter->isHexapusJammed()) {
        Cancel();
        return;
    }
    Robot::shooter->runHexapusMotor(amt);
}

void RunHexapus::Interrupted() {
    End();
}

void RunHexapus::End() {
    Robot::shooter->runHexapusMotor(0);
}

RunHexapus::RunHexapus(double amt) : Command() {
    this->amt = amt;
    //motorController = RobotMap::hexapusController;
    // Requires(Robot::shooter.get())
}
