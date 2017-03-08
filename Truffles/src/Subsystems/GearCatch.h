//
// Created by Jason Markham on 2/14/17.
//

#ifndef TRUFFLES_GEARCATCH_H
#define TRUFFLES_GEARCATCH_H

#include "Commands/Subsystem.h"
#include "LinearActuator.h"
#include <memory>
class GearCatch : public Subsystem {
 public:
  GearCatch();

  void moveOut();

  void moveIn();
  /**
   * WARNING: be careful about calling this!
   */
  void chill();

  /**
   *
   * @param position a value between 0 and 1
   */
  void setPosition(double position);

  /**
   *
   * @return a value between 0 and 1
   */
  double getPosition();

 private:
  std::shared_ptr<LinearActuator> actuator1;
  std::shared_ptr<LinearActuator> actuator2;
};

#endif  // TRUFFLES_GEARCATCH_H
