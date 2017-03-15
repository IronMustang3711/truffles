//
// Created by Jason Markham on 3/3/17.
//

#include "ZeroEncoders.h"
#include "../../Robot.h"

void ZeroEncoders::Execute() {
	Robot::chassis->zeroEncoders();
}
