/*
 * PlaceGear.h
 *
 *  Created on: 6 Mar 2017
 *      Author: steffen
 */

#ifndef SRC_COMMANDS_AUTO_PLACEGEAR_H_
#define SRC_COMMANDS_AUTO_PLACEGEAR_H_

#include "Commands/CommandGroup.h"
#include "Commands/auto/DriveStraight.h"
#include "Commands/auto/RotateCommand.h"
#include "Commands/auto/StrafeCommand.h"
#include "Commands/auto/PixyRotate.h"
#include "Commands/auto/PixyStrafe.h"

class PlaceGear: public CommandGroup {
public:
	PlaceGear(int mode);
	virtual ~PlaceGear();
};

#endif /* SRC_COMMANDS_AUTO_PLACEGEAR_H_ */
