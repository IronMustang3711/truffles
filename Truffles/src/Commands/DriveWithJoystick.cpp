
#include "DriveWithJoystick.h"

DriveWithJoystick::DriveWithJoystick() :
		Command("Drive with joystick") {
	Requires(Robot::chassis.get());

}

void DriveWithJoystick::Execute() {
	Robot::chassis->teleopDrive(Robot::oi->driverJoystick);
}

bool DriveWithJoystick::IsFinished() {
	return false;
}

void DriveWithJoystick::Interrupted() {
	DriverStation::ReportWarning("trace:DriveWithJoystick:Interrupted"); //TODO: remove when no longer needed;
	Robot::chassis->stop();
}

void DriveWithJoystick::End() {
	Robot::chassis->stop();
}
