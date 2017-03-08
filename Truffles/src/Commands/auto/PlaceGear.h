/*
 * PlaceGear.h
 *
 *  Created on: 6 Mar 2017
 *      Author: steffen
 */

#ifndef SRC_COMMANDS_AUTO_PLACEGEAR_H_
#define SRC_COMMANDS_AUTO_PLACEGEAR_H_

#include "Commands/CommandGroup.h"
#include "DriveStraight.h"
#include "RotateCommand.h"
#include "StrafeCommand.h"
#include "PixyRotate.h"
#include "PixyStrafe.h"
#include "../TogglePixyLight.h"

class PlaceGear : public CommandGroup {
 public:
  PlaceGear(int mode);
  virtual ~PlaceGear();
};

#endif /* SRC_COMMANDS_AUTO_PLACEGEAR_H_ */
