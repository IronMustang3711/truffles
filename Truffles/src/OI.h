// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#ifndef OI_H
#define OI_H

#include "WPILib.h"

class Btn : public Button {
 public:
  Btn(Joystick* joystick, int buttonNumber);

  bool Get() override;
  Joystick* joystick;
  int buttonNumber;
};
class DriverJoystick : public Joystick {
 public:
  DriverJoystick();

  Btn* winchUp;
  Btn* ballIntake;
  Btn* changeFront;
};
class ShooterJoystick : public Joystick {
 public:
  ShooterJoystick();

  Btn* winchUp;
  Btn* winchDown;
  Btn* winchStop;
  Btn* runHexapus;
  Btn* runIntake;
  Btn* shoot;
  Btn* unjam;
  Btn* gearCatchIn;
  Btn* gearCatchOut;
};

class OI {

 public:
  std::shared_ptr<DriverJoystick> driverJoystick;
  std::shared_ptr<ShooterJoystick> shooterJoystick;

  void initSmartDashboardCommands();

 public:
  OI();

};

#endif