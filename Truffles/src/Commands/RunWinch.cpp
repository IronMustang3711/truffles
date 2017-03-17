#include "RunWinch.h"
#include "../Robot.h"

RunWinch::RunWinch(double speed) :
		Command() {
	m_speed = speed;
	Requires(Robot::winch.get());
}

void RunWinch::Initialize() {
	Robot::winch->runWinchMotor(m_speed);
}

void RunWinch::Execute() {
	Robot::winch->runWinchMotor(m_speed);
}

bool RunWinch::IsFinished() {
	return false;
}

void RunWinch::End() {
	Robot::winch->runWinchMotor(0.0);
}
void RunWinch::Interrupted() {
	End();
}

RunWinch* RunWinch::createGoUpCommand() {
	return new RunWinch(1.0);
}

RunWinch* RunWinch::createHoldCommand() {
	return new RunWinch(0.3);
}

RunWinch* RunWinch::createDownCommand() {
	return new RunWinch(-0.3);
}

RunWinch* RunWinch::createStopCommand() {
	return new RunWinch(0.0);
}
