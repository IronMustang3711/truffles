#include "Commands/auto/RotateWheelsOnce.h"
#include "Commands/auto/SimpleDriveForward.h"
#include "OI.h"

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
#include "Commands/auto/DriveStraight.h"
#include "Commands/auto/RotateWheelsOnce.h"
#include "Commands/auto/AutonomousCommandFactory.h"
#include "Commands/Ringlights.h"
#include "Commands/SolenoidToggle.h"
#include "Commands/JogBackCommand.h"
#include "Commands/JogBackSimple.h"
#include "Commands/ReloadChoosers.h"

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
	//DriverStation::ReportWarning("OI begin");
	driverJoystick.reset(new DriverJoystick());
	shooterJoystick.reset(new ShooterJoystick());

	initSmartDashboardCommands();
	//DriverStation::ReportWarning("OI done");
}
void OI::initSmartDashboardCommands() {
	SmartDashboard::PutData("zero encoders", new ZeroEncoders());
	SmartDashboard::PutData("reload choosers", new ReloadChoosers());
//	SmartDashboard::PutData("drive straight(100)", new DriveStraight(100));
//	SmartDashboard::PutData("drive straight(timed)", new SimpleDriveForward());
//	SmartDashboard::PutData("rotate(+30deg)", new RotateCommand(30));
//	SmartDashboard::PutData("strafe", new StrafeCommand(20));
//	SmartDashboard::PutData("rotate wheels 1x", new RotateWheelseOnce());

//	SmartDashboard::PutData(
//			new SolenoidToggle(RobotMap::lightsRed, "perimeter lights(red)"));
//	SmartDashboard::PutData(
//			new SolenoidToggle(RobotMap::lightsGreen,
//					"perimeter lights(green)"));
//	SmartDashboard::PutData(
//			new SolenoidToggle(RobotMap::lightsBlue, "perimeter lights(blue)"));

	SmartDashboard::PutData("ringlights", new Ringlights());

//	SmartDashboard::PutData("jog",new JogBackCommand());
//	SmartDashboard::PutData("jog(simple)", new JogBackSimple());
}

Btn::Btn(Joystick* j, int b) :
		joystick(j), buttonNumber(b) {
}

bool Btn::Get() {
	return joystick->GetRawButton(buttonNumber);
}

DriverJoystick::DriverJoystick() :
		Joystick(0), winchUp(new Btn(this, 8)), ballIntake(new Btn(this, 3)), changeFront(
				new Btn(this, 1)), jogBack(new Btn(this, 2)) {
	winchUp->WhileHeld(RunWinch::createGoUpCommand());
	winchUp->WhenReleased(RunWinch::createHoldCommand());
	ballIntake->WhileHeld(new RunIntake());
	changeFront->WhenPressed(new ToggleRobotFront());
	jogBack->WhenPressed(new JogBackSimple());
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
	//gearCatchToggle->WhenPressed(new GearCatchToggle());
	runHexapus->WhileHeld(new RunHexapusCommand());
	unjam->WhenPressed(new UnjamHexapus(new StopHexapus()));
}
