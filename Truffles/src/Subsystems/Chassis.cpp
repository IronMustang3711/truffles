
#include "Chassis.h"
#include "../Commands/DriveWithJoystick.h"
#include "../RobotMap.h"

Chassis::Chassis() : Subsystem("Chassis") {
  leftFront = RobotMap::leftFrontController;
  leftRear = RobotMap::leftRearController;
  rightFront = RobotMap::rightFrontController;
  rightRear = RobotMap::rightRearController;
  drive = RobotMap::chassisDrive;
}

void Chassis::InitDefaultCommand() {
  SetDefaultCommand(new DriveWithJoystick());
}

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
//TODO: we should probably make sure that rotateAngle is 0 for autonomous
  dashboardTelemetry();
}
void Chassis::stop() {
	drive->StopMotor();
}

void Chassis::dashboardTelemetry() {
  // TODO: does this work??
  std::map<std::string, CANTalon*> talons = {{"front left", leftFront.get()},
                                             {"front right", rightFront.get()},
                                             {"rear left", leftRear.get()},
                                             {"rear right", rightRear.get()}};

  for (auto it = talons.begin(); it != talons.end(); ++it) {
    SmartDashboard::PutNumber(it->first + "_position",
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

void Chassis::prepareForTeleop() {
  // TODO
}

// void Chassis::initMagicMode() {}
//
// void Chassis::initRegularMode() {}

void Chassis::toggleRobotFrontDirection() {
  rotateAngle = (rotateAngle == 0.0 ? 90.0 : 0.0);
}

void Chassis::TankDrive(double leftValue,
                        double rightValue,
                        bool squaredInputs) {
  drive->TankDrive(leftValue, rightValue, squaredInputs);
}

void Chassis::Drive(double outputMagnitude, double curve) {
  drive->Drive(outputMagnitude, curve);
}

void Chassis::MecanumDrive_Polar(double magnitude,
                                 double direction,
                                 double rotation) {
  drive->MecanumDrive_Polar(magnitude, direction, rotation);
}

double Chassis::getLeftRearVelocity() {
  return leftRear->GetSpeed();
}

double Chassis::getLeftRearPosition() {
  return leftRear->GetPosition();
}

double Chassis::getRightRearPosition() {
  return rightRear->GetPosition();
}

double Chassis::getRightRearVelocity() {
  return rightRear->GetSpeed();
}

double Chassis::getLeftFrontVelocity() {
  return leftFront->GetSpeed();
}
double Chassis::getLeftFrontPosition() {
  return leftFront->GetPosition();
}
double Chassis::getRightFrontPosition() {
  return rightFront->GetPosition();
}
double Chassis::getRightFrontVelocity() {
  return rightFront->GetSpeed();
}

double Chassis::getHeading() {
  return RobotMap::ahrs->GetAngle();
}
