//
// Created by Jason Markham on 3/3/17.
//

#include "DriveStraight.h"
#include "../../Robot.h"


DriveStraight::DriveStraight()
    : SimpleCommand("DriveStraight"), timer{} {
    	updater = std::make_unique<Notifier>(&DriveStraight::update,this);
  drive = Robot::chassis;
  SetTimeout(3.5);
  Requires(drive.get());
}

    void DriveStraight::update(){

    }

void DriveStraight::operator()() {
  double t = timer.Get();
  double output = 0.0;
  if (t <= duration) {
   output = motorOut*t;
  } else if(t>duration && t<=2*duration){
	 output=motorOut;
  } else if(t>2*duration && t<=3*duration){
	  output = motorOut - motorOut*(t-2*duration);
  } else {
	  Cancel();
  }
  double angle = useGyro ? -0.5*drive->getHeading() : 0.0;
  drive->Drive(output,angle);
}

void DriveStraight::Initialize() {
	 motorOut = SmartDashboard::GetNumber("motor out", 0.5);
	 useGyro = SmartDashboard::GetBoolean("use gyro", true);
	 duration = SmartDashboard::GetBoolean("drive straight segment duration", 1.0);
	 SetTimeout(duration+0.5);
	drive->zeroEncoders();
  updater->StartPeriodic(0.01);
  timer.Reset();
  timer.Start();
}

void DriveStraight::Execute() {
	SmartDashboard::PutBoolean("encoder velocity(left)",drive->getLeftRearVelocity());
	SmartDashboard::PutBoolean("encoder velocity(right)",drive->getRightRearVelocity());

}

void DriveStraight::End() {
  updater->Stop();
  timer.Stop();
  SmartDashboard::PutNumber("final position(left)", drive->getLeftRearPosition());
  SmartDashboard::PutNumber("final position(right)", drive->getRightRearPosition());
}
