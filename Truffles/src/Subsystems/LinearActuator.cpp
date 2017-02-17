/*
 * LinearActuator.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: jason
 */

#include "LinearActuator.h"
/*
 *
 *
 * helpful:
 https://www.chiefdelphi.com/forums/showpost.php?p=1640566&postcount=8

 less helpful:
 https://www.chiefdelphi.com/forums/showthread.php?t=155087&highlight=L16
 */

LinearActuator::LinearActuator(int channel) :  Servo(channel) {
	  SetBounds(2.0, 0.0, 0.0, 0.0, 1.0);
	  SetPeriodMultiplier(kPeriodMultiplier_4X); //?
    SetSpeed(1.0);
    SetSpeed(-1);
}

void LinearActuator::SetPosition(double value) {
    PWM::SetPosition(value);
}

//void LinearActuator::Set(double value) {
//    SetSpeed(2*(value-0.5));
//    Servo::Set(value);
//}

