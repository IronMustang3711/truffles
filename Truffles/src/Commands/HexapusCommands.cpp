//
// Created by Jason Markham on 2/20/17.
//

#include "HexapusCommands.h"
#include "../Robot.h"
static const double UNJAM_TIME = 0.15;

RunHexapusCommand::RunHexapusCommand() :
		SimpleCommand("run hexapus command") {
}

RunHexapusCommand::State RunHexapusCommand::getState() {
	return state;
}
void RunHexapusCommand::transition(State newState) {
	State prevState = state;

	if (prevState == State::RUNNING) {
		if (runCount <= 20) {
			jamCount++;
		}
		runCount = 0;
	} else if (prevState != State::UNJAM) {
		jamCount = 0;
	}

	switch (newState) {
	case State::INITIAL_OFF:
		unjamTimer.Stop();
		unjamTimer.Reset();
		Robot::hexapus->stop();
		break;
	case State::RUNNING:
		Robot::hexapus->run();
		break;
	case State::UNJAM:
		if (jamCount > 5) {
			Cancel();
		} else {
			unjamTimer.Reset();
			unjamTimer.Start();
			Robot::hexapus->unjam();
		}
		break;
	case State::WAITING_FOR_SHOOTER:
		Robot::hexapus->stop();
		break;
	}

	SmartDashboard::PutString("hexapus state", StateName(newState));

	state = newState;
}
std::string RunHexapusCommand::StateName(State state) {
	switch (state) {
	case State::INITIAL_OFF:
		return "initial/off";
	case State::WAITING_FOR_SHOOTER:
		return "waiting for shooter";
	case State::RUNNING:
		return "running";
	case State::UNJAM:
		return "unjamming";

	}
	return "lol";
}

void RunHexapusCommand::Initialize() {
	transition(State::INITIAL_OFF);
}

void RunHexapusCommand::Execute() {
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
		runCount++;
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
void RunHexapusCommand::End() {
	transition(State::INITIAL_OFF);
}

StopHexapus::StopHexapus() :
		InstantCommand("stop hexapus") {
}

void StopHexapus::Execute() {
	Robot::hexapus->stop();
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

UnjamHexapus::UnjamHexapus(Command* c) :
		SimpleCommand("unjam hexapus", 0.1), nextCommand(c) {
}
