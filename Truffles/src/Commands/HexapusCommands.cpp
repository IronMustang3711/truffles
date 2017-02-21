//
// Created by Jason Markham on 2/20/17.
//

#include "HexapusCommands.h"
#include "../Robot.h"

StopHexapus::StopHexapus() : InstantCommand("stop") {}

void StopHexapus::Execute() {
  Robot::shooter->runHexapusMotor(0.0);
}

RunHexapus::RunHexapus()
    : SimpleCommand("run"), unjamHexapus{this}, stopHexapus{} {}

void RunHexapus::Execute() {
  if (disable) {
    DriverStation::ReportError("Hexapus disabled because of too many Jams!");
    Cancel();
    return;
  }
  if (Robot::shooter->isHexapusJammed()) {
    jamCount++;
    SmartDashboard::PutNumber("current", Robot::shooter->getHexapusCurrent());
    SmartDashboard::PutNumber("jam count", jamCount);
    Robot::shooter->stopHexapusMotor();
    Cancel();
    unjamHexapus.Start();
  } else {
    jamCount = 0;
    Robot::shooter->runHexapusMotor();
  }

  if (jamCount == 5) {
    disable = true;
  }
}

void RunHexapus::End() {
  stopHexapus.Start();
}

void UnjamHexapus::Execute() {
  if (Robot::shooter->isHexapusJammed()) {
    Cancel();
  }
  Robot::shooter->unjamHexapusMotor();
}

void UnjamHexapus::End() {
  if (nextCommand != nullptr)
    nextCommand->Start();
}

UnjamHexapus::UnjamHexapus(Command* c)
    : SimpleCommand("unjam", 0.1), nextCommand(c) {}
