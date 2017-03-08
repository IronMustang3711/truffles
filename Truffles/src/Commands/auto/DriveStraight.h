//
// Created by Jason Markham on 3/3/17.
//

#ifndef TRUFFLES_DRIVESTRAIGHT_H
#define TRUFFLES_DRIVESTRAIGHT_H

#include "../SimpleCommand.h"
#include "../../Subsystems/Chassis.h"
#include <memory>
#include "Notifier.h"
#include "Timer.h"
//TODO: see if this works (better than DriveStraight)
class DriveStraight2 : public PIDCommand {
 public:
  DriveStraight2(double distanceInInches);
  void Initialize() override;
  void Execute() override;
  void End() override;
  bool IsFinished() override;

  virtual double ReturnPIDInput() override;
  virtual void UsePIDOutput(double output) override;

 private:
  Timer timer{};
  double startAngle = 0;
  double motorOut = 0.5;
  double duration = 1.0;
  double targetDistance=0;
};

class DriveStraight : public SimpleCommand {
 public:
  DriveStraight(double distanceInInches);

 protected:
  void Initialize() override;

  void Execute() override;

  void End() override;

 public:
  void update();

 private:
  Timer timer;
  std::shared_ptr<Chassis> drive;
  std::unique_ptr<Notifier> updater;
  double motorOut = 0.5;
  double duration = 1.0;
  bool useGyro = true;
  double initialHeading = 0.0;
  double targetDistance;
};

#endif  // TRUFFLES_DRIVESTRAIGHT_H
