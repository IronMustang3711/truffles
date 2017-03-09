
#ifndef _ROBOT_H
#define _ROBOT_H

#include "Commands/Command.h"
#include "LiveWindow/LiveWindow.h"
#include "RobotMap.h"
#include "WPILib.h"

#include "Commands/AutonomousCommand.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/Intake.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Winch.h"
#include "Subsystems/Lights.h"

#include "OI.h"
#include "Subsystems/GearCatch.h"
#include "Subsystems/Hexapus.h"

class Robot : public IterativeRobot {
 public:
  std::unique_ptr<Command> autonomousCommand;
  static std::unique_ptr<OI> oi;
  LiveWindow* lw = LiveWindow::GetInstance();
  static std::shared_ptr<Chassis> chassis;
  static std::shared_ptr<Shooter> shooter;
  static std::shared_ptr<Hexapus> hexapus;
  static std::shared_ptr<Intake> intake;
  static std::shared_ptr<Winch> winch;
  static std::shared_ptr<GearCatch> gearCatch;
  static std::shared_ptr<Lights> lights;

  virtual void RobotInit();
  virtual void DisabledInit();
  virtual void DisabledPeriodic();
  virtual void AutonomousInit();
  virtual void AutonomousPeriodic();
  virtual void TeleopInit();
  virtual void TeleopPeriodic();
  virtual void TestPeriodic();
  void updateAllianceColor();

  void dashboardUpdate();

  static void vision();
};
#endif
