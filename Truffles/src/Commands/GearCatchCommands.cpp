//
// Created by Jason Markham on 2/14/17.
//

#include "GearCatchCommands.h"

GearCatchCommand::GearCatchCommand(const std::string& name) : Command(name) {
  Requires(Robot::intake.get());
}

void GearCatchCommand::Interrupted() {
  Cancel();
}

// TODO: still pretty hackey
void GearCatchCommand::End() {
  Robot::gearCatch->moveIn();
}

bool GearCatchCommand::IsFinished() {
  return IsCanceled() || IsTimedOut();
}

void GearCatchCommand::Initialize() {
  Robot::gearCatch->moveOut();  // TODO Is this necessary?
}

GearCatchOut::GearCatchOut() : GearCatchCommand("Gear Catch -> Out") {
  SetTimeout(2.0);
}

GearCatchIn::GearCatchIn() : GearCatchCommand("Gear Catch -> In") {
  SetTimeout(2.0);
}

void GearCatchOut::Execute() {
  Robot::gearCatch->moveOut();
}

void GearCatchIn::Execute() {
  double prevPosition = Robot::gearCatch->getPosition();
  double nextPosition = prevPosition - 0.01;
  if (nextPosition > 0.0001) {
    Robot::gearCatch->setPosition(nextPosition);
  } else {
    Robot::gearCatch->moveIn();
    Cancel();
  }

  // SmartDashboard::PutNumber("gear actuator position", nextPosition);
}

void GearCatchInUnpowered::Execute() {
  Robot::gearCatch->chill();
}

GearCatchInUnpowered::GearCatchInUnpowered()
    : GearCatchCommand("Gear Catch in (undriven)") {}

GearCatchToggle::GearCatchToggle() : Command("Gear Catch Toggle") {
  currentCommand = &chill;
  SetInterruptible(false);
}

void GearCatchToggle::End() {
  Command::End();
}

void GearCatchToggle::Initialize() {
  currentCommand = &chill;
}

void GearCatchToggle::Execute() {
  if (currentCommand == nullptr || !currentCommand->IsRunning())
    changeCommand();
}

void GearCatchToggle::setCurrentCommand(GearCatchCommand* cmd) {
  currentCommand = cmd;
}

bool GearCatchToggle::IsFinished() {
  return false;
}

void GearCatchToggle::changeCommand() {
  if (currentCommand == &catchIn)
    setCurrentCommand(&catchOut);
  else if (currentCommand == &catchOut)
    setCurrentCommand(&catchIn);
  else
    setCurrentCommand(&chill);
}
