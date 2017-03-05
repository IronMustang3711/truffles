#include "TogglePixyLight.h"

void TogglePixyLight::Execute() {
  RobotMap::pixyRinglight->Set(!RobotMap::pixyRinglight->Get());
}

TogglePixyLight::TogglePixyLight() : InstantCommand() {}
