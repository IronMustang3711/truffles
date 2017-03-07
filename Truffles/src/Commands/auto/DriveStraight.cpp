//
// Created by Jason Markham on 3/3/17.
//

#include "DriveStraight.h"
#include "../../Robot.h"




//p,i,d,f, update rate(seconds)
DriveStraight2::DriveStraight2() : PIDCommand("Rotate",1,0,0,0.1,0.01) {

 Requires(Robot::chassis.get());
 SetTimeout(3.0);
 SetPIDSourceType(PIDSourceType::kDisplacement);
}



void DriveStraight2::Initialize() {
	startAngle = Robot::chassis->getHeading(); //or calibrate?

	SetSetpoint(startAngle);
}

void DriveStraight2::Execute() {

}

bool DriveStraight2::IsFinished(){
	return IsTimedOut() || IsCanceled();
}


void DriveStraight2::End() {
	Robot::chassis->Drive(0,0);
}

double DriveStraight2::ReturnPIDInput(){
	return Robot::chassis->getHeading();
}

void DriveStraight2::UsePIDOutput(double out){
	 double t = timer.Get();
	  double output = 0.0;
	  if (t <= duration) {
	    output = motorOut * t;
	  } else if (t > duration && t <= 2 * duration) {
	    output = motorOut;
	  } else if (t > 2 * duration && t <= 3 * duration) {
	    output = motorOut - motorOut * (t - 2 * duration);
	  } else {
	    Cancel();
	  }
	Robot::chassis->MecanumDrive_Cartesian(0, output, out,0);
}


DriveStraight::DriveStraight() : SimpleCommand("DriveStraight"), timer{} {
  updater = std::make_unique<Notifier>(&DriveStraight::update, this);
  drive = Robot::chassis;
  SetTimeout(3.5);
  Requires(drive.get());
}

void DriveStraight::update() {
	 double t = timer.Get();
	  double output = 0.0;
	  if (t <= duration) {
	    output = motorOut * t;
	  } else if (t > duration && t <= 2 * duration) {
	    output = motorOut;
	  } else if (t > 2 * duration && t <= 3 * duration) {
	    output = motorOut - motorOut * (t - 2 * duration);
	  } else {
	    Cancel();
	  }
	//  double angle = useGyro ? -0.5 * drive->getHeading() : 0.0;
	  drive->MecanumDrive_Polar(output, 0, 0);
}

//void DriveStraight::operator()() {
//  double t = timer.Get();
//  double output = 0.0;
//  if (t <= duration) {
//    output = motorOut * t;
//  } else if (t > duration && t <= 2 * duration) {
//    output = motorOut;
//  } else if (t > 2 * duration && t <= 3 * duration) {
//    output = motorOut - motorOut * (t - 2 * duration);
//  } else {
//    Cancel();
//  }
//  double angle = useGyro ? -0.5 * drive->getHeading() : 0.0;
//  drive->Drive(output, angle);
//}

void DriveStraight::Initialize() {
  motorOut = SmartDashboard::GetNumber("motor out", 0.5);
  useGyro = SmartDashboard::GetBoolean("use gyro", true);
  duration = SmartDashboard::GetBoolean("drive straight segment duration", 1.0);
  SetTimeout(duration + 0.5);
  drive->zeroEncoders();
  updater->StartPeriodic(0.01);
  timer.Reset();
  timer.Start();
}

void DriveStraight::Execute() {
  SmartDashboard::PutBoolean("encoder velocity(left)",
                             drive->getLeftRearVelocity());
  SmartDashboard::PutBoolean("encoder velocity(right)",
                             drive->getRightRearVelocity());
}

void DriveStraight::End() {
  updater->Stop();
  timer.Stop();
  SmartDashboard::PutNumber("final position(left)",
                            drive->getLeftRearPosition());
  SmartDashboard::PutNumber("final position(right)",
                            drive->getRightRearPosition());
}
