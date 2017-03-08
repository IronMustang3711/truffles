/*
 * PixyCommand.h
 *
 *  Created on: 6 Mar 2017
 *      Author: steffen
 */

#ifndef SRC_COMMANDS_AUTO_PIXYCOMMAND_H_
#define SRC_COMMANDS_AUTO_PIXYCOMMAND_H_

#include "../../Pixy.h"
#include "Commands/Subsystem.h"
#include "../../Robot.h"

enum PixyMovement {
	NONE,
	LEFT,
	RIGHT
};

class PixyCommand: public Command {
public:
	PixyCommand();
	virtual ~PixyCommand();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

	double widthAspect;
	double heightAspect;
	int leftMargin;
	int rightMargin;
	double marginAspect;

	PixyMovement rotate;
	PixyMovement strafe;
private:
};

#endif /* SRC_COMMANDS_AUTO_PIXYCOMMAND_H_ */
