//
// Created by Jason Markham on 2/20/17.
//

#include "HexapusCommands.h"
#include "../Robot.h"
static const int UNJAM_TIME = 0.15;
MyHexapusCommand::MyHexapusCommand() : SimpleCommand("my hexapus command") {}

MyHexapusCommand::State MyHexapusCommand::getState() {
  return state;
}
void MyHexapusCommand::transition(State newState) {
  switch (newState) {
    case State::INITIAL_OFF:
      Robot::hexapus->stop();
      break;
    case State::RUNNING:
      jamCount = 0;
      Robot::hexapus->run();
      break;
    case State::UNJAM:
      if (jamCount++ == 7) {
        Cancel();
      } else {
        unjamTimer.Reset();
        Robot::hexapus->unjam();
      }
  }

  state = newState;
}

void MyHexapusCommand::Initialize() {
  transition(State::INITIAL_OFF);
}
void MyHexapusCommand::Execute() {
  switch (state) {
    case State::INITIAL_OFF:
      transition(State::WAITING_FOR_SHOOTER);
      break;
    case State::WAITING_FOR_SHOOTER:
      if (Robot::shooter->state == Shooter::STEADY) {
        transition(State::RUNNING);
      }
      break;
    case State::RUNNING:
      if (Robot::hexapus->isJammed()) {
        transition(State::UNJAM);
      } else if (Robot::shooter->state != Shooter::STEADY) {
        transition(State::WAITING_FOR_SHOOTER);
      }
      break;
    case State::UNJAM:
      if (unjamTimer.Get() >= UNJAM_TIME) {
        transition(State::INITIAL_OFF);
      } else if (Robot::hexapus->isJammed()) {
        transition(State::UNJAM);
      }
      break;
  }
}
void MyHexapusCommand::End() {
  transition(State::INITIAL_OFF);
}

StopHexapus::StopHexapus() : InstantCommand("stop") {}

void StopHexapus::Execute() {
  Robot::hexapus->stop();
}

RunHexapus::RunHexapus()
    : SimpleCommand("run"), unjamHexapus{this}, stopHexapus{} {}

void RunHexapus::Execute() {
  //  if (disable) {
  //    DriverStation::ReportError("Hexapus disabled because of too many
  //    Jams!");
  //    Cancel();
  //    return;
  //  }

  if (Robot::shooter->state != Shooter::STEADY) {
    // Robot::hexapus->run(0.3);
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

  if (jamCount % 5 == 0) {
    DriverStation::ReportError("Hexapus is jammed!");
    // disable = true;
  }
}

void RunHexapus::End() {
  Robot::hexapus->stop();
  // stopHexapus.Start();
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
