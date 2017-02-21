//
// Created by Jason Markham on 2/14/17.
//

#include "GearCatch.h"
#include "../Commands/GearCatchCommands.h"
#include "../RobotMap.h"
/**
 * see
 https://www.chiefdelphi.com/forums/showthread.php?t=154631&highlight=linear+actuator+servo
 *

 */
GearCatch::GearCatch() : Subsystem("Gear Catch") {
  actuator1 = RobotMap::gearCatchActuator1;
  actuator2 = RobotMap::gearCatchActuator2;
//Moved to LinearActuator
//  actuator1->SetBounds(2.0, 0, 0, 0, 1.0);
//  actuator2->SetBounds(2.0, 0, 0, 0, 1.0);
}

void GearCatch::InitDefaultCommand() {
  SetDefaultCommand(new GearCatchInUnpowered());
}

void GearCatch::moveOut() {
  setPosition(0.615);
}

/*
 * from the above link:
 * ... -The basic set function does not seem to work for whatever reason.
 * Using setSpeed(1) and setSpeed(-1) properly calls setMaxPWM and setMinPWM
 * wheres set(1) and set(0) do not properly call them.
 */
void GearCatch::setPosition(double position) {
    //Moved to LinearActuator
//  double scaledPosition = 2 * position - 1;
//
//  actuator1->SetSpeed(scaledPosition);
//  actuator2->SetSpeed(scaledPosition);
  //    // Servo.set expects input in [0,1]
    actuator1->Set(position);
    actuator2->Set(position);
}

void GearCatch::moveIn() {
  setPosition(0);
}
void GearCatch::chill() {
  // TODO does this work better than SetPosition(0) ?
  actuator1->SetOffline();
  actuator2->SetOffline();
}

double GearCatch::getPosition() {
  return actuator1->Get();
}

void GearCatch::moveTo(GearCatch::Position p) {
  switch (p) {
    case ACCEPT_BALLS:
      setPosition(0.615);
      break;
    case ACCEPT_GEARS:
      setPosition(0.0);
      break;
    case CHILL:
        chill();
      break;
  }
}
