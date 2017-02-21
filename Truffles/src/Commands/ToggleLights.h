//
// Created by Jason Markham on 2/20/17.
//

#ifndef TRUFFLES_TOGGLELIGHTS_H
#define TRUFFLES_TOGGLELIGHTS_H

#include "../Robot.h"
#include "Commands/Subsystem.h"

class ToggleLights : public InstantCommand {
 public:
  ToggleLights();

 protected:
  void Execute() override;
};

#endif  // TRUFFLES_TOGGLELIGHTS_H
