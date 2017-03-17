//
// Created by Jason Markham on 2/14/17.
//

#include "GearCatchCommands.h"

GearCatchCommand::GearCatchCommand(const std::string& name) :
		InstantCommand(name) {
	Requires(Robot::gearCatch.get());
}

// WARNING: DONT DO THIS BECAUSE IT WILL IMMEDIATELY CANCEL ANY MOVEMENT!!!!
// void GearCatchCommand::End() {
// // Robot::gearCatch->chill();
//}

GearCatchOut::GearCatchOut() :
		GearCatchCommand("Gear Catch -> Out") {
}

GearCatchIn::GearCatchIn() :
		GearCatchCommand("Gear Catch -> In") {
}

void GearCatchOut::Execute() {
	gearCatch->moveOut();
}

void GearCatchIn::Execute() {
	gearCatch->moveIn();
}

void GearCatchInUnpowered::Execute() {
	gearCatch->chill();
}

GearCatchInUnpowered::GearCatchInUnpowered() :
		GearCatchCommand("Gear Catch in (undriven)") {
}

GearCatchToggle::GearCatchToggle() :
		InstantCommand("Gear Catch Toggle") {
	currentCommand = &catchIn;
}

void GearCatchToggle::Execute() {
	changeCommand();
}

void GearCatchToggle::setCurrentCommand(GearCatchCommand* cmd) {
	// SmartDashboard::PutString("trace", cmd->GetName());
	currentCommand = cmd;
	currentCommand->Start();
}

void GearCatchToggle::changeCommand() {
	if (currentCommand != nullptr && currentCommand->GetID() == catchIn.GetID())
		setCurrentCommand(&catchOut);
	else
		setCurrentCommand(&catchIn);
}
