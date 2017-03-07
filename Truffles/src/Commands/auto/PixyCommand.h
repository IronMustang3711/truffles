/*
 * PixyCommand.h
 *
 *  Created on: 6 Mar 2017
 *      Author: steffen
 */

#ifndef SRC_COMMANDS_AUTO_PIXYCOMMAND_H_
#define SRC_COMMANDS_AUTO_PIXYCOMMAND_H_

#include "Commands/Subsystem.h"

class PixyCommand {
public:
	PixyCommand();
	virtual ~PixyCommand();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	Pixy* pixy;
};

#endif /* SRC_COMMANDS_AUTO_PIXYCOMMAND_H_ */
