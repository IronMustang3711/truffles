//
// Created by Jason Markham on 2/20/17.
//

#include "HexapusCommands.h"
#include "../Robot.h"

StopHexapus::StopHexapus() : InstantCommand("stop") {}

void StopHexapus::Execute() {
  Robot::hexapus->stop();
}

RunHexapus::RunHexapus()
    : SimpleCommand("run"), unjamHexapus{this}, stopHexapus{} {}

void RunHexapus::Execute() {
//  if (disable) {
//    DriverStation::ReportError("Hexapus disabled because of too many Jams!");
//    Cancel();
//    return;
//  }
  if (Robot::shooter->isHexapusJammed()) {
  if (disable) {
    DriverStation::ReportError("Hexapus disabled because of too many Jams!");
    Cancel();
    return;
  }
  if (Robot::hexapus->isJammed()) {
    jamCount++;
    // SmartDashboard::PutNumber("current",
    // Robot::shooter->getHexapusCurrent());
    SmartDashboard::PutNumber("hexapus jam count", jamCount);
    Robot::hexapus->stop();
    Cancel();
    unjamHexapus.Start();
  } else {
    jamCount = 0;
    Robot::hexapus->run();
  }

  if (jamCount == 5) {
      DriverStation::ReportError("Hexapus is jammed!");
    //disable = true;
  }
}

void RunHexapus::End() {
    Robot::shooter->stopHexapusMotor();
  //stopHexapus.Start();
}

void UnjamHexapus::Execute() {
  if (Robot::hexapus->isJammed()) {
    Cancel();
  }
  Robot::hexapus->unjam();
}

void UnjamHexapus::End() {
  if (nextCommand != nullptr)
    nextCommand->Start();
}

UnjamHexapus::UnjamHexapus(Command* c)
    : SimpleCommand("unjam", 0.1), nextCommand(c) {}
