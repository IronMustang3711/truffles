// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/AutonomousCommand.h"
#include "Commands/DriveWithJoystick.h"
#include "Commands/GearCatchCommands.h"
#include "Commands/RunHexapus.h"
#include "Commands/RunIntake.h"
#include "Commands/RunShooter.h"
#include "Commands/RunWinch.h"
#include "Commands/ToggleLights.h"

class HexapusButton : public JoystickButton {
  // bool buttonReleased = false;
  bool jamDetected = false;

 public:
  HexapusButton(GenericHID* joystick, int buttonNumber)
      : JoystickButton(joystick, buttonNumber) {}

  bool Get() override {
    bool buttonPressed = JoystickButton::Get();
    if (buttonPressed) {
      if (jamDetected) {
        return false;
      } else {
        bool jam = Robot::shooter->isHexapusJammed();
        if (jam) {
          jamDetected = true;
          return false;
        }
      }
    } else {
      if (jamDetected) {
        jamDetected = false;
      }
      return JoystickButton::Get();
    }
    // shouldnt get here:
    return JoystickButton::Get() && !Robot::shooter->isHexapusJammed();
  }
};

class RotateFront : public InstantCommand {
  DriveWithJoystick* drive = new DriveWithJoystick();

 protected:
  void Initialize() override {
    drive->Start();
    drive->toggle();
  }

  void Execute() override {}
  void End() {}
};

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

/**
 * Operator Input Setup
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
  // Process operator interface input here.
  // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
  driverJoystick.reset(new Joystick(0));
  shooterJoystick.reset(new Joystick(1));

  driverWinchUp.reset(new JoystickButton(driverJoystick.get(), 8));
  driverWinchUp->WhileHeld(new RunWinch(1.0));
  driverWinchUp->WhenReleased(new RunWinch(0.3));

  shooterWinchDown.reset(new JoystickButton(shooterJoystick.get(), 9));
  shooterWinchDown->WhileHeld(new RunWinch(-0.3));

  shooterWinchZero.reset(new JoystickButton(shooterJoystick.get(), 10));
  shooterWinchZero->WhenPressed(new RunWinch(0));

  shooterWinchUp.reset(new JoystickButton(shooterJoystick.get(), 11));
  shooterWinchUp->WhileHeld(new RunWinch(1.0));
  shooterWinchUp->WhenReleased(new RunWinch(0.3));

  driverBallIntake.reset(new JoystickButton(driverJoystick.get(), 3));
  driverBallIntake->WhileHeld(new RunIntake(-0.6));
  driverChangeFront.reset(new JoystickButton(driverJoystick.get(), 1));
  driverChangeFront->WhenPressed(new RotateFront());

  shooterShoot.reset(new JoystickButton(shooterJoystick.get(), 2));
  shooterShoot->ToggleWhenPressed(new RunShooter());

  shooterRunHexapus.reset(new HexapusButton(shooterJoystick.get(), 1));
  shooterRunHexapus->WhileHeld(new RunHexapus(0.75));
  shooterRunHexapus->WhenReleased(new ReAddDefaultHexapusCommand());

  gearCatchToggle.reset(new JoystickButton(shooterJoystick.get(), 5));
  gearCatchToggle->WhenPressed(new GearCatchToggle());

  shooterGearCatchOut.reset(new JoystickButton(shooterJoystick.get(), 6));
  shooterGearCatchOut->WhenPressed(new GearCatchOut());

  shooterGearIntakeToggle.reset(new JoystickButton(shooterJoystick.get(), 8));
  shooterGearIntakeToggle->WhenPressed(new GearCatchToggle());

  RunHexapus* hexapus = new RunHexapus(-0.5);
  hexapus->timeOut(0.1);
  shooterUnjam.reset(new JoystickButton(shooterJoystick.get(), 7));
  shooterUnjam->WhenPressed(hexapus);
  // shooterUnjam->WhenReleased(new ReAddDefaultHexapusCommand());

  shooterRunIntake.reset(new JoystickButton(shooterJoystick.get(), 3));
  shooterRunIntake->WhileHeld(new RunIntake(-0.6));

  initSmartDashboardCommands();

  // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

void OI::initSmartDashboardCommands() {
  // SmartDashboard Buttons
  SmartDashboard::PutData("RunIntake: in", new RunIntake(1));
  SmartDashboard::PutData("RunIntake: out", new RunIntake(-1));
  SmartDashboard::PutData("RunWinch: down", new RunWinch(-1));
  SmartDashboard::PutData("RunWinch: up", new RunWinch(1));
  SmartDashboard::PutData("RunWinch: upslow", new RunWinch(0.3));
  SmartDashboard::PutData("RunShooter", new RunShooter());
  SmartDashboard::PutData("DriveWithJoystick", new DriveWithJoystick());
  SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());
  SmartDashboard::PutData("Hexapus", new RunHexapus(1.0));
  //
  SmartDashboard::PutData("Gear catch: in (undriven)",
                          new GearCatchInUnpowered());
  SmartDashboard::PutData("gear catch: toggle", new GearCatchToggle());
  SmartDashboard::PutData("Gear catch: in", new GearCatchIn());
  SmartDashboard::PutData("Gear catch: out", new GearCatchOut());
  SmartDashboard::PutData("Toggle lights", new ToggleLights());
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<Joystick> OI::getDriverJoystick() {
  return driverJoystick;
}

std::shared_ptr<Joystick> OI::getShooterJoystick() {
  return shooterJoystick;
}

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

ReAddDefaultHexapusCommand::ReAddDefaultHexapusCommand() : InstantCommand() {}

void ReAddDefaultHexapusCommand::Exeute() {
  Robot::oi->shooterRunHexapus->WhileHeld(new RunHexapus(0.75));
}
