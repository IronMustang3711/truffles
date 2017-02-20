//
// Created by Jason Markham on 2/20/17.
//

#include "ToggleLights.h"
#include "../RobotMap.h"

void ToggleLights::Execute() {
    RobotMap::lights->Set(!RobotMap::lights->Get());
}
