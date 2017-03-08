/*
 * AutonomousCommandFactory.cpp
 *
 *  Created on: Mar 7, 2017
 *      Author: jason
 */

#include <Commands/auto/AutonomousCommandFactory.h>
#include <DriverStation.h>
using namespace frc;
std::shared_ptr<Command> AutonomousCommandFactory::createAutonomousCommand() {

	auto alliance = DriverStation::GetInstance().GetAlliance();
	int position = DriverStation::GetInstance().GetLocation();
	std::shared_ptr<Command> ptr;

	/*
	 * position 2(either side) : go straight
	 *
	 * red:
	 * 	1.) straight, right
	 * 	3.)straight, left
	 *
	 *blue:
	 *	1.) straight, right
	 *	3.) straight, left
	 *
	 */

	return ptr;

}



