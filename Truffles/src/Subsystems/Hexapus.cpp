//
// Created by Jason Markham on 2/21/17.
//

#include "Hexapus.h"
#include "../RobotMap.h"

Hexapus::Hexapus() : Subsystem("hexapus") {
  hexapusController = RobotMap::hexapusController;
  ;
}

bool Hexapus::isJammed() {
  return getMotorCurrent() >= 6.0;
}

double Hexapus::getMotorCurrent() {
  return RobotMap::powerDistributionPanel->GetCurrent(2);
}
void Hexapus::run(double speed) {
  hexapusController->Set(-speed);
}
void Hexapus::run() {
  run(0.5);
}

void Hexapus::stop() {
  run(0);
}

void Hexapus::unjam() {
  run(-0.6);
}
