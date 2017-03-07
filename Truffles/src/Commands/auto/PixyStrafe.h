/*
 * PixyStrafe.h
 *
 *  Created on: 6 Mar 2017
 *      Author: steffen
 */

#ifndef SRC_COMMANDS_AUTO_PIXYSTRAFE_H_
#define SRC_COMMANDS_AUTO_PIXYSTRAFE_H_

#include "PixyCommand.h"

class PixyStrafe: public PixyCommand {
public:
	PixyStrafe();
	virtual ~PixyStrafe();

	virtual void Execute();
	virtual bool IsFinished();
};

#endif /* SRC_COMMANDS_AUTO_PIXYSTRAFE_H_ */
