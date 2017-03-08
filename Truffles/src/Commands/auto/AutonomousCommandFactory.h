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
class AutonomousCommandFactory {
public:

	static std::shared_ptr<Command> createAutonomousCommand();
};

#endif /* SRC_COMMANDS_AUTO_AUTONOMOUSCOMMANDFACTORY_H_ */
