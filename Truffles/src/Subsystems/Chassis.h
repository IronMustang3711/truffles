#ifndef CHASSIS_H
#define CHASSIS_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <CANTalon.h>
#include <vector>

/**
 *
 *
 * @author ExampleAuthor
 */
class Chassis: public Subsystem {
private:
	std::shared_ptr<CANTalon> leftFront;
	std::shared_ptr<CANTalon> leftRear;
	std::shared_ptr<CANTalon> rightFront;
	std::shared_ptr<CANTalon> rightRear;
	std::shared_ptr<RobotDrive> drive;

public:
	Chassis();
	void InitDefaultCommand();
	/**
	 * delegates to MecanumDrive_Cartesian
	 * @param stickPosition
	 * @param gyroAngle
	 */
	void MecanumDrive(std::shared_ptr<Joystick> stickPosition,
			double gyroAngle = 0.0);
	void AutoDrive(double fwdSpeed, double rotateSpeed);
	void MecanumDrive_Cartesian(double x, double y, double rotation,
			double gyroAngle = 0.0);
	void MecanumDrive_Polar(double magnitude, double direction,
			double rotation);
	void Drive(double outputMagnitude, double curve);
	void TankDrive(double leftValue, double rightValue,
	bool squaredInputs = true);
	void stop();

	double getRightFrontCurrent();
	double getRightRearCurrent();
	double getLeftFrontCurrent();
	double getLeftRearCurrent();

	double getLeftRearVelocity();
	double getLeftRearPosition();
	double getRightRearPosition();
	double getRightRearVelocity();
	double getLeftFrontVelocity();
	double getLeftFrontPosition();
	double getRightFrontPosition();
	double getRightFrontVelocity();

	double getHeading();

	void zeroEncoders();

	//  CANTalon* getTalons();

	void toggleRobotFrontDirection();

	void prepareForTeleop();

	//  void initMagicMode();
	//  void initRegularMode();
	void dashboardTelemetry();
	double rotateAngle = 0.0;
};

#endif
