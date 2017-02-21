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
    Robot::oi->shooterRunHexapus->CancelWhenActive(this);

    // TODO: leak!, also this is totally dumb and hackey.
    RunHexapus* cmd = new RunHexapus(-0.75);
    cmd->SetTimeout(0.2);
    Robot::oi->shooterRunHexapus->WhileHeld(cmd);
    // Cancel();
    End();

  } else {
    Robot::shooter->runHexapusMotor(amt);
  }
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

RunHexapus *RunHexapus::createUnjamCommand() {
  RunHexapus* hexapus = new RunHexapus(-0.5);
  hexapus->timeOut(0.1);
  return hexapus;
}



RunHexapus::RunHexapus() : RunHexapus(0.75){
}
