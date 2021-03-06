#ifndef _ROBOT_H
#define _ROBOT_H

#include "Commands/Command.h"
#include "LiveWindow/LiveWindow.h"
#include "RobotMap.h"
#include "WPILib.h"

#include "Subsystems/Chassis.h"
#include "Subsystems/Intake.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Winch.h"
#include "Subsystems/Lights.h"


#include "OI.h"
#include "Subsystems/GearCatch.h"
#include "Subsystems/Hexapus.h"
#include "Subsystems/CollisionDetector.h"

class Robot: public IterativeRobot {
public:
	static std::unique_ptr<OI> oi;
	LiveWindow* lw = LiveWindow::GetInstance();
	static std::shared_ptr<Chassis> chassis;
	static std::shared_ptr<Shooter> shooter;
	static std::shared_ptr<Hexapus> hexapus;
	static std::shared_ptr<Intake> intake;
	static std::shared_ptr<Winch> winch;
	static std::shared_ptr<GearCatch> gearCatch;
	static std::shared_ptr<Lights> lights;
	static std::shared_ptr<CollisionDetector> collisionDetector;

	virtual void RobotInit();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	void autonomousDidFinish();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();
	void updateAllianceColor();

	void dashboardUpdate();

	static Robot* robot;


	frc::SendableChooser<frc::Command*> chooser{};





private:
	std::unique_ptr<frc::Command> autonomousCommand;
	bool autoDidRun = false;
};
#endif
