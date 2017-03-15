/*
 * AutonomousCommandFactory.cpp
 *
 *  Created on: Mar 7, 2017
 *      Author: jason
 */

#include "AutonomousCommandFactory.h"
#include <DriverStation.h>
#include "Noop.h"

using namespace frc;
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
}

Command* AutonomousCommandFactory::position2Auto() {
}

Command* AutonomousCommandFactory::position3Auto() {
}

Command* AutonomousCommandFactory::driveStraightAuto() {

}

Command* AutonomousCommandFactory::doNothingAuto() {
	return new Noop();
}

void AutonomousCommandFactory::setupChooser(
		SendableChooser<Command*>& chooser) {
	chooser.AddDefault("auto",
			AutonomousCommandFactory::createAutonomousCommand());
	//rod insisted on having these even though the "auto" mode should handle all three cases.
	//dont remove.
	chooser.AddObject("position 1 auto", position1Auto());
	chooser.AddObject("position 2 auto", position2Auto());
	chooser.AddObject("position 3 auto", position3Auto());
	chooser.AddObject("drive straight", driveStraightAuto());
	chooser.AddObject("do nothing", doNothingAuto());
}
