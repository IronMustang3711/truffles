//
// Created by Jason Markham on 3/3/17.
//

#ifndef TRUFFLES_DRIVESTRAIGHT_H
#define TRUFFLES_DRIVESTRAIGHT_H

#include "../SimpleCommand.h"
#include "../../Subsystems/Chassis.h"

class DriveStraight : public SimpleCommand {
 public:
  DriveStraight();

 protected:
  void Initialize() override;

  void Execute() override;

  void End() override;

 public:
  void operator()();
  void update();

 private:
  Timer timer;
  std::shared_ptr<Chassis> drive;
  std::unique_ptr<Notifier> updater;
  double motorOut = 0.5;
  double duration = 1.0;
  bool useGyro = true;
};

#endif  // TRUFFLES_DRIVESTRAIGHT_H
