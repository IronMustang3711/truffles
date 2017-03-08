
#include "RunIntake.h"
#include "../Robot.h"

RunIntake::RunIntake(double speed) : Command() {
  m_speed = speed;
}

void RunIntake::Initialize() {}

void RunIntake::Execute() {
  Robot::intake->run(m_speed);
}

bool RunIntake::IsFinished() {
  return IsCanceled() || IsTimedOut();
}

void RunIntake::End() {
  Robot::intake->run(0.0);
}

void RunIntake::Interrupted() {
  End();
}

RunIntake::RunIntake() : RunIntake(-0.6) {}
