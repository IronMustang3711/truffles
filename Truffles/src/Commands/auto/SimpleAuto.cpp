/*
 * SimpleAuto.cpp
 *
 *  Created on: Mar 7, 2017
 *      Author: jason
 */

#include "SimpleAuto.h"
#include <Commands/Command.h>
#include "../../Robot.h"

class SimpleDriveStraight : public Command {
 public:
  SimpleDriveStraight() : Command("drive straight(simple)") {}

  virtual void Initialize() override {}
  virtual void Execute() override {}
  virtual void End() override {}
  virtual bool IsFinished() override { return false; }
};

class SimpleRotate : public Command {
 public:
  SimpleRotate() : Command("drive straight(simple)") {}

  virtual void Initialize() override {}
  virtual void Execute() override {}
  virtual void End() override {}
};
