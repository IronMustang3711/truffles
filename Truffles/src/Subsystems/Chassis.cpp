#include "Chassis.h"
#include "../Commands/DriveWithJoystick.h"
#include "../RobotMap.h"
/**
 *   gearbox ratio 8.45:1
 wheelbase== 26"
 encoder 360 : 1
 theoretically: 1 revolution = 18.8"
 */
Chassis::Chassis() :
		Subsystem("Chassis") {
	leftFront = RobotMap::leftFrontController;
	leftRear = RobotMap::leftRearController;
	rightFront = RobotMap::rightFrontController;
	rightRear = RobotMap::rightRearController;
	drive = RobotMap::chassisDrive;
    pegSliderLeft = -1;
    pegSliderRight = -1;
}

void Chassis::InitDefaultCommand() {
	SetDefaultCommand(new DriveWithJoystick());
}
/**
 * delegates to Chassis::teleopDrive(double x, double y, double rotation,
		double gyroAngle)
 * @param stickPosition
 * @param gyroAngle
 */
void Chassis::teleopDrive(std::shared_ptr<Joystick> stickPosition,
		double gyroAngle) {
	double x = stickPosition->GetX();  // this is driverJoystick left/right
	double y = stickPosition->GetY();  // this is forward/backward
	double z = stickPosition->GetZ();  // this is twist left/right

	teleopDrive(x, y, z, gyroAngle);
}
/**
 *delegates to void Chassis::MecanumDrive_Cartesian(double x, double y, double rotation,
		double gyroAngle)
		@see void Chassis::MecanumDrive_Cartesian(double x, double y, double rotation,
		double gyroAngle)
 * @param x
 * @param y
 * @param rotation
 * @param gyroAngle
 */
void Chassis::teleopDrive(double x, double y, double rotation,
		double gyroAngle) {
	x = pow(x, 3);
	y = pow(y, 3);
	rotation = pow(rotation, 3) * 0.3; // limit to 10% to make it easier to control
	MecanumDrive_Cartesian(x, y, rotation, gyroAngle + rotateAngle);
}

void Chassis::AutoDrive(double fwdSpeed, double rotateSpeed) {
	MecanumDrive_Cartesian(0, -fwdSpeed, rotateSpeed);
}

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
void Chassis::MecanumDrive_Cartesian(double x, double y, double rotation,
		double gyroAngle) {

//TODO: we should probably make sure that rotateAngle is 0 for autonomous
	drive->MecanumDrive_Cartesian(x,y,rotation,gyroAngle);
	dashboardTelemetry();
}
void Chassis::stop() {
	drive->StopMotor();
}

void Chassis::dashboardTelemetry() {
	std::map<std::string, CANTalon*> talons = {
			{ "front left", leftFront.get() },
			{ "front right", rightFront.get() },
			{ "rear left", leftRear.get() }, { "rear right", rightRear.get() } };

	for (auto it = talons.begin(); it != talons.end(); ++it) {
		SmartDashboard::PutNumber(it->first + " enc_position",
				it->second->GetEncPosition());
		SmartDashboard::PutNumber(it->first + " position",
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

}

// void Chassis::initMagicMode() {}
//
// void Chassis::initRegularMode() {}

void Chassis::toggleRobotFrontDirection() {
	rotateAngle = (rotateAngle == 0.0 ? 90.0 : 0.0);
}

void Chassis::TankDrive(double leftValue, double rightValue,
bool squaredInputs) {
	drive->TankDrive(leftValue, rightValue, squaredInputs);
}
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
//note wheelbase == 33-34 inches, probably
//6" wheel diameter
void Chassis::Drive(double outputMagnitude, double curve) {
	drive->Drive(outputMagnitude, curve);
}
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
void Chassis::MecanumDrive_Polar(double magnitude, double direction,
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
void Chassis::resetHeading() {
	RobotMap::ahrs->Reset();
	rotateAngle = getHeading();
}




