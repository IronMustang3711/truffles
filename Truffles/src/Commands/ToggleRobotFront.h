//
// Created by Jason Markham on 2/21/17.
//

#ifndef TRUFFLES_TOGGLEROBOTFRONT_H
#define TRUFFLES_TOGGLEROBOTFRONT_H
#include "../Robot.h"
#include "Commands/Subsystem.h"

class ToggleRobotFront : public InstantCommand {
  virtual void Execute() override;
};

#endif  // TRUFFLES_TOGGLEROBOTFRONT_H
