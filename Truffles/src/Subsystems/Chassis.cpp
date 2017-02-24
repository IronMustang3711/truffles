// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "Chassis.h"
#include "../Commands/DriveWithJoystick.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Chassis::Chassis() : Subsystem("Chassis") {
  // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
  leftFront = RobotMap::leftFrontController;
  leftRear = RobotMap::leftRearController;
  rightFront = RobotMap::rightFrontController;
  rightRear = RobotMap::rightRearController;
  drive = RobotMap::chassisDrive;

  // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}

void Chassis::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

  SetDefaultCommand(new DriveWithJoystick());

  // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void Chassis::MecanumDrive(std::shared_ptr<Joystick> stickPosition,
                           double gyroAngle) {
  double x = stickPosition->GetX();  // this is driverJoystick left/right
  double y = stickPosition->GetY();  // this is forward/backward
  double z = stickPosition->GetZ();  // this is twist left/right

  MecanumDrive_Cartesian(x, y, z, gyroAngle);
}

void Chassis::AutoDrive(float fwdSpeed, float rotateSpeed) {  //%NE
  drive->MecanumDrive_Cartesian(0, -fwdSpeed, rotateSpeed);
}

void Chassis::MecanumDrive_Cartesian(double x,
                                     double y,
                                     double rotation,
                                     double gyroAngle) {
  x = pow(x, 3);
  y = pow(y, 3);
  rotation =
      pow(rotation, 3) * 0.3;  // limit to 10% to make it easier to control
  drive->MecanumDrive_Cartesian(x, y, rotation, gyroAngle + rotateAngle);

  dashboardTelemetry();
}

void Chassis::dashboardTelemetry() {
  std::map<std::string, CANTalon*> talons = {{"front left", leftFront.get()},
                                             {"front right", rightFront.get()},
                                             {"rear left", leftRear.get()},
                                             {"rear right", rightRear.get()}};

  for (auto it = talons.begin(); it != talons.end(); ++it) {
    SmartDashboard::PutNumber(it->first + "/position",
                              it->second->GetPosition());
  }
}

double Chassis::getRightFrontCurrent() {
  return RobotMap::powerDistributionPanel->GetCurrent(15);
}

double Chassis::getRightRearCurrent() {
  return RobotMap::powerDistributionPanel->GetCurrent(0);
}

double Chassis::getLeftFrontCurrent() {
  return RobotMap::powerDistributionPanel->GetCurrent(14);
}

double Chassis::getLeftRearCurrent() {
  return RobotMap::powerDistributionPanel->GetCurrent(1);
}

void Chassis::zeroEncoders() {
  rightFront->SetPosition(0);
  rightRear->SetPosition(0);

  leftFront->SetPosition(0);
  leftRear->SetPosition(0);
}

void Chassis::initMagicMode() {}

void Chassis::initRegularMode() {}

void Chassis::toggleRobotFrontDirection() {
  rotateAngle = (rotateAngle == 0.0 ? 90.0 : 0.0);
}
