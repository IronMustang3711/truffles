//
// Created by Jason Markham on 2/13/17.
//

#include "RunHexapus.h"
#include "../Robot.h"

bool RunHexapus::IsFinished() {
  return IsTimedOut() || IsCanceled();
}

void RunHexapus::Initialize() {}

void RunHexapus::Execute() {
  if (Robot::shooter->isHexapusJammed()) {
    std::cout << "jam detected!!!!!" << std::endl;
    Robot::oi->loadButton->CancelWhenActive(this);

    // TODO: leak!
    RunHexapus* cmd = new RunHexapus(-0.75);
    cmd->SetTimeout(0.2);
    Robot::oi->loadButton->WhileHeld(cmd);
    // Cancel();
    End();
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
}

void RunHexapus::timeOut(double timeout) {
  Command::SetTimeout(timeout);
}
