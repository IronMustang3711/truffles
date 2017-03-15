//
// Created by Jason Markham on 3/3/17.
//

#include "DriveStraight.h"
#include "../../Robot.h"

//template<typename T> int sgn(T val) {
//	return (T(0) < val) - (val < T(0));
//}
//template<> int sgn<double>(double);

//These next 2 are from ctre exaple code
/** @param value to cap.
 * @param peak positive double representing the maximum (peak) value.
 * @return a capped value.
 */
double Cap(double value, double peak) {
	if (value < -peak)
		return -peak;
	if (value > +peak)
		return +peak;
	return value;
}
/**
 * Given the robot forward throttle and ratio, return the max
 * corrective turning throttle to adjust for heading.  This is
 * a simple method of avoiding using different gains for
 * low speed, high speed, and no-speed (zero turns).
 */
double MaxCorrection(double forwardThrot, double scale) {
	/* make it positive */
	if (forwardThrot < 0) {
		forwardThrot = -forwardThrot;
	}
	/* max correction is the current forward throttle scaled down */
	forwardThrot *= scale;
	/* ensure caller is allowed at least 10% throttle,
	 * regardless of forward throttle */
	if (forwardThrot < 0.10)
		return 0.10;
	return forwardThrot;
}

//a = 42, b=48
// p,i,d,f, update rate(seconds)
DriveStraight2::DriveStraight2(double distance) :
		PIDCommand("Rotate", 1, 0, 0, 0.1, 0.01), targetDistance(distance) {
	Requires(Robot::chassis.get());
	SetTimeout(5.0);
	SetPIDSourceType(PIDSourceType::kDisplacement);
}

void DriveStraight2::Initialize() {
	startAngle = Robot::chassis->getHeading();  // or calibrate?
	initialEncoderPositionLeft = Robot::chassis->getRightRearPosition();
	initialEncoderPositionRight = Robot::chassis->getLeftRearPosition();
	SetSetpoint(startAngle);
	timer.Reset();
	timer.Start();
}

void DriveStraight2::Execute() {
}

bool DriveStraight2::IsFinished() {
	return IsTimedOut() || IsCanceled();
}

void DriveStraight2::End() {
	Robot::chassis->Drive(0, 0);
}

double DriveStraight2::ReturnPIDInput() {
	return Robot::chassis->getHeading();
}

void DriveStraight2::UsePIDOutput(double headingPID) {
    //TODO headingPID is unused!
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
		return;
	}
	double gyroZ = (double) RobotMap::ahrs->GetRawGyroZ();
	double currentAngle = Robot::chassis->getHeading();
	double turnThrottle = (startAngle - currentAngle) * kPgain - gyroZ * kDgain;
	double maxThrot = MaxCorrection(output, kMaxCorrectionRatio);
	turnThrottle = Cap(turnThrottle, maxThrot);
	/* positive turnThrottle means turn to the left, this can be replaced with ArcadeDrive object, or teams drivetrain object */
//		float left = output - turnThrottle;
//		float right = output + turnThrottle;
//		left = Cap(left, 1.0);
//		right = Cap(right, 1.0);

	Robot::chassis->MecanumDrive_Cartesian(0, output, turnThrottle, 0);
}

DriveStraight::DriveStraight(double distance) :
		Command("DriveStraight"), timer { }, targetDistance(distance) {
	updater = std::make_unique<Notifier>(&DriveStraight::update, this);
	drive = Robot::chassis;
	SetTimeout(5.0);
	Requires(drive.get());
	duration = targetDistance;  //TODO HACK GALORE!
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
	double angle = initialHeading - Robot::chassis->getHeading();

	//  double angle = useGyro ? -0.5 * drive->getHeading() : 0.0;
	// drive->MecanumDrive_Polar(output, 0, 0);
	drive->Drive(output, 0.005 * angle);
}

void DriveStraight::Initialize() {
	motorOut = SmartDashboard::GetNumber("motor out", 0.5);
	useGyro = SmartDashboard::GetBoolean("use gyro", true);
	duration = SmartDashboard::GetNumber("drive straight segment duration",
			1.0);
	SetTimeout(duration + 0.5);
	drive->zeroEncoders();
	updater->StartPeriodic(0.01);
	timer.Reset();
	timer.Start();
}

void DriveStraight::Execute() {
	SmartDashboard::PutNumber("encoder velocity(left)",
			drive->getLeftRearVelocity());
	SmartDashboard::PutNumber("encoder velocity(right)",
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

bool DriveStraight::IsFinished() {
	return IsTimedOut();
}
