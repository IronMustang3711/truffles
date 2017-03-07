/*
 * StrafeCommand.h
 *
 *  Created on: Mar 6, 2017
 *      Author: jason
 */

#ifndef SRC_COMMANDS_AUTO_STRAFECOMMAND_H_
#define SRC_COMMANDS_AUTO_STRAFECOMMAND_H_
#include "../SimpleCommand.h"
#include "../../Subsystems/Chassis.h"
#include <memory>
#include "Notifier.h"
#include "Timer.h"
class StrafeCommand : public Command {
public:
	StrafeCommand();

	virtual bool IsFinished();

};

#endif /* SRC_COMMANDS_AUTO_STRAFECOMMAND_H_ */
