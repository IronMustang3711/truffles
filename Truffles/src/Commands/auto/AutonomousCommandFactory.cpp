/*
 * AutonomousCommandFactory.cpp
 *
 *  Created on: Mar 7, 2017
 *      Author: jason
 */

#include "AutonomousCommandFactory.h"
#include <DriverStation.h>
using namespace frc;
std::shared_ptr<Command> AutonomousCommandFactory::createAutonomousCommand() {
	auto alliance = DriverStation::GetInstance().GetAlliance();
	int position = DriverStation::GetInstance().GetLocation();
	std::shared_ptr<Command> ptr;

	/*
	 * all positions :
	 * 	1.) straight, right
	 * 	2.) straight
	 * 	3.)straight, left
	 *
	 */

	return ptr;
}
