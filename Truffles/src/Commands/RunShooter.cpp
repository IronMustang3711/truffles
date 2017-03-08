// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "RunShooter.h"
#include "../Robot.h"
#include "RunIntake.h"
RunShooter::RunShooter() : Command() {
  Requires(Robot::shooter.get());
}

void RunShooter::Initialize() {
  Robot::shooter->initShooter();
}

void RunShooter::Execute() {
  double throttle = Robot::oi->shooterJoystick->GetZ();

  // sliderValue in [0,1]
  double sliderValue = (-throttle + 1) * 0.5;

  Robot::shooter->runShooterMotor(sliderValue);
}

bool RunShooter::IsFinished() {
  return IsCanceled() || IsTimedOut();
}

void RunShooter::End() {
  Robot::shooter->runShooterMotor(0);
}

void RunShooter::Interrupted() {
  End();
}

RunShooterAndIntake::RunShooterAndIntake()
    : CommandGroup("Run shooter and intake") {
  runShooterCommand = new RunShooter();
  runIntakeCommand = new RunIntake();
  AddParallel(runShooterCommand);
  AddParallel(runIntakeCommand);  // TODO: timeout/periodic?
}
RunShooterAndIntake::~RunShooterAndIntake() {
  delete runShooterCommand;
  delete runIntakeCommand;
  // CommandGroup::~CommandGroup();
}
