/*
 * SimpleAuto.cpp
 *
 *  Created on: Mar 7, 2017
 *      Author: jason
 */

#include "SimpleAuto.h"
#include <Commands/Command.h>
#include "../../Robot.h"
#include "Notifier.h"

class SimpleDriveStraight : public Command {
 public:
  SimpleDriveStraight(double distanceInInches) :
	  Command("drive straight(simple)"),
	  targetDistance(distanceInInches) {}

  virtual void Initialize() override {
	  timer.Reset();
	  timer.Start();
	  notifier.StartPeriodic(0.02);
  }
  virtual void Execute() override {}
  virtual void End() override {
	  timer.Stop();
	  timer.Reset();
  }
  virtual bool IsFinished() override {return false;}

  void doUpdate(){

  }

 private:
  double targetDistance = 0;
  Notifier notifier{&SimpleDriveStraight::doUpdate,this};
  Timer timer{};


};

class SimpleRotate : public Command {
 public:
  SimpleRotate(double targetHeadingInDegrees) : Command("rotate(simple)"),targetHeading(targetHeadingInDegrees) {}

  virtual void Initialize() override{}
  virtual void Execute() override{}
  virtual void End() override{}
  virtual bool IsFinished() override{return false;}

 private:
  double initialHeading=0;
  double targetHeading=0;

};
