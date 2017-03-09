/*
 * StrafeCommand.h
 *
 *  Created on: Mar 6, 2017
 *      Author: jason
 */

#ifndef SRC_COMMANDS_AUTO_STRAFECOMMAND_H_
#define SRC_COMMANDS_AUTO_STRAFECOMMAND_H_
#include "../SimpleCommand.h"
#include "../../Subsystems/Chassis.h"
#include <memory>
#include "Notifier.h"
#include "Timer.h"
class StrafeCommand : public Command {
 public:
  StrafeCommand(double distanceInInches_rightIsPositive);
  virtual void Initialize() override;
  virtual bool IsFinished() override;
  virtual void Execute() override;
  virtual void End() override;

  Timer timer;
  bool rampUp = true;
  std::shared_ptr<Chassis> drive;
  std::unique_ptr<Notifier> updater;
  double initialHeading = 0;
  double targetDistance = 0;
};

#endif /* SRC_COMMANDS_AUTO_STRAFECOMMAND_H_ */
