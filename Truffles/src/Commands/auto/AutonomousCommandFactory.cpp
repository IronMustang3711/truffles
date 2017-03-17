/*
 * AutonomousCommandFactory.cpp
 *
 *  Created on: Mar 7, 2017
 *      Author: jason
 */

#include <Commands/auto/SimpleDriveForward.h>
#include "AutonomousCommandFactory.h"
#include <DriverStation.h>
#include "Noop.h"
#include "DriveStraight.h"
#include "../../Robot.h"
#include "RotateCommand.h"
#include "PlaceGear.h"

using namespace frc;

class PositionOneOrThreeSequence: public CommandGroup {
public:
	PositionOneOrThreeSequence(bool onTheRight) :
			CommandGroup("position one or three sequence") {
		Requires(Robot::chassis.get());
		AddSequential(new DriveStraight(70), 3.5);
		double angle = 30.0 * (onTheRight ? 1 : -1);
		AddSequential(new RotateCommand(angle), 2.0);
		AddSequential(new PlaceGear());

	}

};


Command* AutonomousCommandFactory::createAutonomousCommand() {

	int position = DriverStation::GetInstance().GetLocation();

	switch (position) {
	case 1:
		return position1Auto();
	case 2:
		return position2Auto();
	case 3:
		return position3Auto();
	default:
		return doNothingAuto();

	}

}

Command* AutonomousCommandFactory::position1Auto() {
	return new PositionOneOrThreeSequence(false);
}

Command* AutonomousCommandFactory::position2Auto() {
	CommandGroup* g = new CommandGroup("position 2  auto");
	g->AddSequential(new DriveStraight(80),3.0);
	g->AddSequential(new PlaceGear());
	return g;
}

Command* AutonomousCommandFactory::position3Auto() {
	return new PositionOneOrThreeSequence(true);

}

Command* AutonomousCommandFactory::driveStraightAuto() {
	return new DriveStraight(120.0);
}

Command* AutonomousCommandFactory::doNothingAuto() {
	return new Noop();
}

void AutonomousCommandFactory::setupChooser(
		SendableChooser<Command*>& chooser) {
	chooser.AddObject("xxx auto",
			AutonomousCommandFactory::createAutonomousCommand());
	chooser.AddObject("xxx position 1 auto", position1Auto());
	chooser.AddObject("xxx position 2 auto", position2Auto());
	chooser.AddObject("xxx position 3 auto", position3Auto());
	chooser.AddDefault("xxx drive forward", driveStraightAuto());
	chooser.AddDefault("drive forward(timed)",new SimpleDriveForward());
	chooser.AddObject("do nothing", doNothingAuto());
}
