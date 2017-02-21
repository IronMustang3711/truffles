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

  void InitDefaultCommand() override;

  // TODO: I put this stuff here to help implement value ramping in this class
  // instead of a Command, but now Im not sure if it's a good idea.

  //  Position getState();
  //
  //  bool stateTransitionComplete();
  //   void moveTo(Position p);
  enum Position { ACCEPT_BALLS = 0, ACCEPT_GEARS, CHILL };

 private:
  std::shared_ptr<LinearActuator> actuator1;
  std::shared_ptr<LinearActuator> actuator2;
  Position state = Position::CHILL;
  bool stateTransitionFinished = true;

  void moveTo(Position p);
};

#endif  // TRUFFLES_GEARCATCH_H
