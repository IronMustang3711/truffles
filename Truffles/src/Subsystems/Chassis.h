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
	void teleopDrive(std::shared_ptr<Joystick> driveJoystick, double gyroAngle =
			0.0);
	void teleopDrive(double x, double y, double rotation,
			double gyroAngle = 0.0);

	void AutoDrive(double fwdSpeed, double rotateSpeed);
	/**
	 * Drive method for Mecanum wheeled robots.
	 *
	 * A method for driving with Mecanum wheeled robots. There are 4 wheels
	 * on the robot, arranged so that the front and back wheels are toed in 45
	 * degrees.
	 * When looking at the wheels from the top, the roller axles should form an X
	 * across the robot.
	 *
	 * This is designed to be directly driven by joystick axes.
	 *
	 * @param x         The speed that the robot should drive in the X direction.
	 *                  [-1.0..1.0]
	 * @param y         The speed that the robot should drive in the Y direction.
	 *                  This input is inverted to match the forward == -1.0 that
	 *                  joysticks produce. [-1.0..1.0]
	 * @param rotation  The rate of rotation for the robot that is completely
	 *                  independent of the translation. [-1.0..1.0]
	 * @param gyroAngle The current angle reading from the gyro.  Use this to
	 *                  implement field-oriented controls.
	 */
	void MecanumDrive_Cartesian(double x, double y, double rotation,
			double gyroAngle = 0.0);
	/**
	 * Drive method for Mecanum wheeled robots.
	 *
	 * A method for driving with Mecanum wheeled robots. There are 4 wheels
	 * on the robot, arranged so that the front and back wheels are toed in 45
	 * degrees.
	 * When looking at the wheels from the top, the roller axles should form an X
	 * across the robot.
	 *
	 * @param magnitude The speed that the robot should drive in a given direction.
	 *                  [-1.0..1.0]
	 * @param direction The direction the robot should drive in degrees. The
	 *                  direction and maginitute are independent of the rotation
	 *                  rate.
	 * @param rotation  The rate of rotation for the robot that is completely
	 *                  independent of the magnitute or direction. [-1.0..1.0]
	 */
	void MecanumDrive_Polar(double magnitude, double direction,
			double rotation);
	/**
	 * Drive the motors at "outputMagnitude" and "curve".
	 * Both outputMagnitude and curve are -1.0 to +1.0 values, where 0.0 represents
	 * stopped and not turning. curve < 0 will turn left and curve > 0 will turn
	 * right.
	 *
	 * The algorithm for steering provides a constant turn radius for any normal
	 * speed range, both forward and backward. Increasing m_sensitivity causes
	 * sharper turns for fixed values of curve.
	 *
	 * This function will most likely be used in an autonomous routine.
	 *
	 * @param outputMagnitude The speed setting for the outside wheel in a turn,
	 *                        forward or backwards, +1 to -1.
	 * @param curve           The rate of turn, constant for different forward
	 *                        speeds. Set curve < 0 for left turn or curve > 0 for
	 *                        right turn.
	 *
	 * Set curve = e^(-r/w) to get a turn radius r for wheelbase w of your robot.
	 * Conversely, turn radius r = -ln(curve)*w for a given value of curve and
	 * wheelbase w.
	 */
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
	void resetHeading();

	//  CANTalon* getTalons();

	void toggleRobotFrontDirection();

	void prepareForTeleop();

	//  void initMagicMode();
	//  void initRegularMode();
	void dashboardTelemetry();
	double rotateAngle = 0.0;

	int pegSliderLeft;
	int pegSliderRight;
};

#endif
