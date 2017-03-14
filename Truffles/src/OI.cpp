
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
 * Operator Input Setup //TODO update/validate description
 * ====================
 *
 * Driver Joystick
 * ------------------
 * 	-Toggle pickup: button 2
 * 	-switch robot front: button 1
 * 	-rope climb: button 5 - go up while held, hold on release
 * 	-driving: x,y,twist
 *
 * 	Secondary Joystick
 * 	---------------------
 * 	-shoot(toggle hexapus): button 1
 * 	-shoot(toggle flywheel): button 2
 * 	-shoot(flywheel speed): throttle
 * 	-shoot(hexapus unjam/go backwards a little): button 4
 * 	-Gear Catch Toggle(in/out): button 3
 *
 */
OI::OI() {
  driverJoystick.reset(new DriverJoystick());
  shooterJoystick.reset(new ShooterJoystick());

  initSmartDashboardCommands();
}
void OI::initSmartDashboardCommands() {
  // SmartDashboard Buttons
  SmartDashboard::PutData("RunIntake", new RunIntake());
  //  SmartDashboard::PutData("RunWinch: down", RunWinch::createDownCommand());
  //  SmartDashboard::PutData("RunWinch: up", RunWinch::createGoUpCommand());
  //  SmartDashboard::PutData("RunWinch: upslow",
  //  RunWinch::createHoldCommand());
  SmartDashboard::PutData("RunShooter", new RunShooter());
  SmartDashboard::PutData("RunShooterAndIntake", new RunShooterAndIntake());
  //  SmartDashboard::PutData("DriveWithJoystick", new DriveWithJoystick());
  //  SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());
  //
  //  SmartDashboard::PutData("Gear catch: in (undriven)",
  //                          new GearCatchInUnpowered());
  //  SmartDashboard::PutData("gear catch: toggle", new GearCatchToggle());
  //  SmartDashboard::PutData("Gear catch: in", new GearCatchIn());
  //  SmartDashboard::PutData("Gear catch: out", new GearCatchOut());
  //  SmartDashboard::PutData("Toggle lights", new ToggleLights());

  SmartDashboard::PutData("zero encoders", new ZeroEncoders());
  SmartDashboard::PutData("driveStraight", new DriveStraight(1));
  SmartDashboard::PutData("driveStraight2",new DriveStraight2(1));
  SmartDashboard::PutData("driveStraightSimple",new SimpleDriveStraight(1));

  SmartDashboard::PutData("rotate", new RotateCommand(45));
  SmartDashboard::PutData("strafe", new StrafeCommand(1));

  //  SmartDashboard::PutData(
  //      new SolenoidToggle(RobotMap::lightsRed, "red lights"));
  //  SmartDashboard::PutData(
  //      new SolenoidToggle(RobotMap::lightsGreen, "green lights"));
  //  SmartDashboard::PutData(
  //      new SolenoidToggle(RobotMap::lightsBlue, "blue lights"));

  SmartDashboard::PutData(
      new SolenoidToggle(RobotMap::pixyRinglight, "pixy ringlight"));
  SmartDashboard::PutData(
      new SolenoidToggle(RobotMap::rearRingLight, "rear ringlight"));

  SmartDashboard::PutData("ringlights",new RingLights());
}

Btn::Btn(Joystick* j, int b) : joystick(j), buttonNumber(b) {}

bool Btn::Get() {
  return joystick->GetRawButton(buttonNumber);
}

DriverJoystick::DriverJoystick()
    : Joystick(0),
      winchUp(new Btn(this, 8)),
      ballIntake(new Btn(this, 3)),
      changeFront(new Btn(this, 1)) {
  winchUp->WhileHeld(RunWinch::createGoUpCommand());
  winchUp->WhenReleased(RunWinch::createHoldCommand());
  ballIntake->WhileHeld(new RunIntake());
  changeFront->WhenPressed(new ToggleRobotFront());
}

ShooterJoystick::ShooterJoystick()
    : Joystick(1),
      winchUp(new Btn(this, 11)),
      winchDown(new Btn(this, 9)),
      winchStop(new Btn(this, 10)),
      runHexapus(new Btn(this, 1)),
      runIntake(new Btn(this, 3)),
      shoot(new Btn(this, 2)),
      unjam(new Btn(this, 7)),
      gearCatchToggle(new Btn(this, 5)) {
  winchDown->WhileHeld(RunWinch::createDownCommand());
  winchStop->WhenPressed(RunWinch::createStopCommand());
  winchUp->WhileHeld(RunWinch::createGoUpCommand());
  winchUp->WhenReleased(RunWinch::createHoldCommand());

  shoot->ToggleWhenPressed(new RunShooter());
  // RunShooterAndIntake is another option, but the intake draws too much
  // current
  // and messes with shooter tuning. It seems like the talon should be able to
  // adapt to this,
  // but whatever...

  runIntake->WhileHeld(new RunIntake());

  gearCatchToggle->WhenPressed(new GearCatchToggle());

  runHexapus->WhileHeld(new MyHexapusCommand());
  // runHexapus->WhenReleased(new StopHexapus());

  //    {
  //        auto g = new CommandGroup();
  //        g->AddParallel(new RunHexapus());
  //        g->AddParallel(new RunIntake(-0.4));
  //        runHexapus->WhileHeld(g);
  //    }
  // runHexapus->WhenReleased(new StopHexapus());

  unjam->WhenPressed(new UnjamHexapus(new StopHexapus()));
}
