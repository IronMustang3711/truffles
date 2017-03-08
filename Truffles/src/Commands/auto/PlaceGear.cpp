/*
 * PlaceGear.cpp
 *
 *  Created on: 6 Mar 2017
 *      Author: steffen
 */

#include "PlaceGear.h"

PlaceGear::PlaceGear(int mode) : CommandGroup() {
  AddSequential(new TogglePixyLight());  // Turn Pixy light on
  switch (mode) {
    case 0:
      // Robot starting on left side (in front of driver station 1)
      AddSequential(new DriveStraight());
      AddSequential(new RotateCommand());
      AddSequential(new PixyRotate());
      AddSequential(new PixyStrafe());
      AddSequential(new DriveStraight());
      break;
    case 1:
      // Robot starting in the middle (in front of driver station 2)
      AddSequential(new DriveStraight());
      AddSequential(new PixyRotate());
      AddSequential(new PixyStrafe());
      AddSequential(new DriveStraight());
      break;
    case 2:
      // Robot starting on the right side (in front of driver station 3)
      AddSequential(new DriveStraight());
      AddSequential(new RotateCommand());
      AddSequential(new PixyRotate());
      AddSequential(new PixyStrafe());
      AddSequential(new DriveStraight());
      break;
  }
  AddSequential(new TogglePixyLight());  // Turn Pixy light off again
}

PlaceGear::~PlaceGear() {
}
