// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#ifndef SHOOTER_H
#define SHOOTER_H

#include "CANTalon.h"
#include "Commands/Subsystem.h"
#include "Filters/LinearDigitalFilter.h"
#include "Timer.h"
using namespace frc;

class Shooter : public Subsystem {
 public:
  Shooter();

  void InitDefaultCommand();
  /**
   *
   * @param speed in [0,1]
   */
  void runShooterMotor(double speed);
  /**
   *
   * @param d in [0,4500]
   */
  void run(double d);
  double getSetPoint();
  double getVelocity();
  double getClosedLoopError();
  double getOutput();

  double prevSetPoint = 0;
  double prevVelocity = 0;
  double prevClosedLoopError = 0;
  double prevOutput = 0;

  enum State { OFF, INIT, SHOOT, BANG_BANG, STEADY };

  std::string StateName(State s);
  State getState();
  State state = OFF;

  /**
   * setup PID values for the shooter controller.
   */
  void initShooter();

  void transition(State newState);

  void InitTable(std::shared_ptr<ITable> subtable) override;

 private:
  bool isShooting();
  bool isOff(double requestedSpeed);
  std::shared_ptr<CANTalon> shooterController;
  LinearDigitalFilter errorFilter;
  Timer setpointUpdateTimer;
};

#endif
