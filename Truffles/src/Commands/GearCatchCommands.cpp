//
// Created by Jason Markham on 2/14/17.
//

#include "GearCatchCommands.h"
GearCatchCommand::GearCatchCommand(const std::string &name) : frc::Command(name) {}
void GearCatchCommand::Interrupted() {
    End();
}
//TODO: HACKHACKHACKHACK
void GearCatchCommand::End() {
	  Robot::gearCatch->moveInward();
}

bool GearCatchCommand::IsFinished() {
    return IsCanceled() || IsTimedOut();
}

void GearCatchCommand::Initialize() {
	RobotMap::gearCatchActuator1->Set(0.615);

    // Requires(Robot::gearCatch.get());
}


GearCatchVertical::GearCatchVertical() : GearCatchCommand("Gear Catch -> Vertical") {
    //SetTimeout(2.0); //TODO: uncomment?
	Requires(Robot::gearCatch.get());
}

GearCatchOut::GearCatchOut() : GearCatchCommand("Gear Catch -> Out") {
	Requires(Robot::gearCatch.get());
	//SetTimeout(2.0);
}

GearCatchIn::GearCatchIn() : GearCatchCommand("Gear Catch -> In") {
	Requires(Robot::gearCatch.get());
	//SetTimeout(2.0);
	//RobotMap::gearCatchActuator1->Set(0.6);

}

void GearCatchVertical::Execute() {
    Robot::gearCatch->moveVertical();
}


void GearCatchOut::Execute() {
    Robot::gearCatch->moveOutward();
}

void GearCatchIn::Execute() {
	double value = RobotMap::gearCatchActuator1->Get();
	if( value > 0.0001){
		RobotMap::gearCatchActuator1->Set(value-0.01);
		RobotMap::gearCatchActuator2->Set(value-0.01);

	} else {
		Cancel();
	}

	SmartDashboard::PutNumber("gear actuator 1", value);
}

