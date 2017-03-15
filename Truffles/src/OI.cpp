#include "OI.h"

#include "Commands/AutonomousCommand.h"
#include "Commands/DriveWithJoystick.h"
#include "Commands/GearCatchCommands.h"
#include "Commands/RunIntake.h"
#include "Commands/RunShooter.h"
#include "Commands/RunWinch.h"
#include "Commands/ToggleLights.h"
#include "Commands/ToggleRobotFront.h"
#include "Commands/HexapusCommands.h"
#include "Commands/auto/DriveStraight.h"

#include "Commands/auto/ZeroEncoders.h"
#include "Commands/auto/RotateCommand.h"
#include "Commands/auto/StrafeCommand.h"
#include "Commands/auto/SimpleAuto.cpp"
#include "Commands/Ringlights.h"
#include "Commands/SolenoidToggle.h"

/**
 * Operator Input Setup
 * ====================
 *
 * Driver Joystick
 * ------------------
 * 	-Toggle pickup: button 3
 * 	-switch robot front: button 1
 * 	-rope climb: button 8 - go up while held, hold on release
 * 	-driving: x,y,twist
 *
 * 	Secondary Joystick
 * 	---------------------
 * 	-shoot(toggle hexapus): button 1
 * 	-shoot(toggle flywheel): button 2
 * 	-shoot(flywheel speed): throttle
 * 	-shoot(hexapus unjam/go backwards a little): button 7
 * 	-Gear Catch Toggle(in/out): button 5
 * 	-winch up: 11
 * 	-winch hold: 10
 * 	-winch stop: 9
 *
 *
 */
OI::OI() {
	driverJoystick.reset(new DriverJoystick());
	shooterJoystick.reset(new ShooterJoystick());

	initSmartDashboardCommands();
}
void OI::initSmartDashboardCommands() {
	// SmartDashboard Buttons

	SmartDashboard::PutData("zero encoders", new ZeroEncoders());
	SmartDashboard::PutData("driveStraight", new DriveStraight(100));
	SmartDashboard::PutData("driveStraight2", new DriveStraight2(100));
	SmartDashboard::PutData("driveStraightSimple",
			new SimpleDriveStraight(100));

	SmartDashboard::PutData("rotate", new RotateCommand(45));
	SmartDashboard::PutData("strafe", new StrafeCommand(20));

	SmartDashboard::PutData(
			new SolenoidToggle(RobotMap::lightsRed, "perimeter lights(red)"));
	SmartDashboard::PutData(
			new SolenoidToggle(RobotMap::lightsGreen,
					"perimeter lights(green)"));
	SmartDashboard::PutData(
			new SolenoidToggle(RobotMap::lightsBlue, "perimeter lights(blue)"));

	SmartDashboard::PutData("ringlights", new Ringlights());
}

Btn::Btn(Joystick* j, int b) :
		joystick(j), buttonNumber(b) {
}

bool Btn::Get() {
	return joystick->GetRawButton(buttonNumber);
}

DriverJoystick::DriverJoystick() :
		Joystick(0), winchUp(new Btn(this, 8)), ballIntake(new Btn(this, 3)), changeFront(
				new Btn(this, 1)) {
	winchUp->WhileHeld(RunWinch::createGoUpCommand());
	winchUp->WhenReleased(RunWinch::createHoldCommand());
	ballIntake->WhileHeld(new RunIntake());
	changeFront->WhenPressed(new ToggleRobotFront());
}

ShooterJoystick::ShooterJoystick() :
		Joystick(1), winchUp(new Btn(this, 11)), winchDown(new Btn(this, 9)), winchStop(
				new Btn(this, 10)), runHexapus(new Btn(this, 1)), runIntake(
				new Btn(this, 3)), shoot(new Btn(this, 2)), unjam(
				new Btn(this, 7)), gearCatchToggle(new Btn(this, 5)) {
	winchDown->WhileHeld(RunWinch::createDownCommand());
	winchStop->WhenPressed(RunWinch::createStopCommand());
	winchUp->WhileHeld(RunWinch::createGoUpCommand());
	winchUp->WhenReleased(RunWinch::createHoldCommand());

	shoot->ToggleWhenPressed(new RunShooter());

	runIntake->WhileHeld(new RunIntake());
	gearCatchToggle->WhenPressed(new GearCatchToggle());
	runHexapus->WhileHeld(new MyHexapusCommand());
	unjam->WhenPressed(new UnjamHexapus(new StopHexapus()));
}
