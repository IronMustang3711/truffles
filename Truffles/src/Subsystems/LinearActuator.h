/*
 * LinearActuator.h
 *
 *  Created on: Feb 17, 2017
 *      Author: jason
 */

#ifndef SRC_SUBSYSTEMS_LINEARACTUATOR_H_
#define SRC_SUBSYSTEMS_LINEARACTUATOR_H_

#include <Servo.h>

class LinearActuator : public frc::Servo {
 public:
  LinearActuator(int channel);
/**
 *
 * @param value in [0,1]
 * */
  void SetPosition(double value) override;

};

#endif /* SRC_SUBSYSTEMS_LINEARACTUATOR_H_ */
