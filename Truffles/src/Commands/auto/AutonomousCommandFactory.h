/*
 * AutonomousCommandFactory.h
 *
 *  Created on: Mar 7, 2017
 *      Author: jason
 */

#ifndef SRC_COMMANDS_AUTO_AUTONOMOUSCOMMANDFACTORY_H_
#define SRC_COMMANDS_AUTO_AUTONOMOUSCOMMANDFACTORY_H_
#include <memory>
#include <commands/Command.h>
#include <WPILib.h>
/*
 * all positions :
 * 	1.) straight, right
 * 	2.) straight
 * 	3.)straight, left
 *
 */
class AutonomousCommandFactory {
public:

	/**
	 *
	 * @return An autonomous command to place a gear. Figures out position via frc api.
	 */
	static Command* createAutonomousCommand();
	/**
	 *
	 * @return a command that goes straight,rotates right,then goes foward attempting to place a peg
	 */
	static Command* position1Auto();
	/**
	 *
	 * @return a command that goes straight then goes foward attempting to place a peg
	 */
	static Command* position2Auto();
	/**
	 *
	 * @return a command that goes straight,rotates left,then goes foward attempting to place a peg
	 */
	static Command* position3Auto();
	/**
	 *
	 * @return a command that will drive straight, past the 100" 5 pt. mark.
	 */
	static Command* driveStraightAuto();
	/**
	 *
	 * @return a lame command that does nothing
	 */
	static Command* doNothingAuto();

	/**
	 * populates a chooser with auto commands
	 * @param chooser the chooser to add the auto commands to
	 */
	static void setupChooser(SendableChooser<Command*>& chooser);

};

#endif /* SRC_COMMANDS_AUTO_AUTONOMOUSCOMMANDFACTORY_H_ */
