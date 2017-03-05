#ifndef TRUFFLES_TOGGLEPIXYLIGHT_H
#define TRUFFLES_TOGGLEPIXYLIGHS_H

#include "../Robot.h"
#include "Commands/Subsystem.h"

class TogglePixyLight : public InstantCommand {
 public:
  TogglePixyLight();

 protected:
  void Execute() override;
};

#endif  // TRUFFLES_TOGGLEPIXYLIGHT_H
