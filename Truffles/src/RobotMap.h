// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "CANTalon.h"
#include "SmartDashboard/SmartDashboard.h"
#include <AHRS.h>
#include "Subsystems/LinearActuator.h"

const int ENCODER_PULSES_PER_REVOLUTION = 20;

class RobotMap {
public:
	static std::shared_ptr<CANTalon> leftFrontController;
	static std::shared_ptr<CANTalon> leftRearController;
	static std::shared_ptr<CANTalon> rightFrontController;
	static std::shared_ptr<CANTalon> rightRearController;
	static std::shared_ptr<RobotDrive> chassisDrive;
	static std::shared_ptr<CANTalon> shooterController;
	static std::shared_ptr<Spark> intakeController;
	static std::shared_ptr<Spark> winchController;
	static std::shared_ptr<Spark> hexapusController;
	static std::shared_ptr<LinearActuator> gearCatchActuator1;
	static std::shared_ptr<LinearActuator> gearCatchActuator2;
	static std::shared_ptr<AHRS> ahrs;
	static std::shared_ptr<Solenoid> lightsRed;
	static std::shared_ptr<Solenoid> lightsGreen;
	static std::shared_ptr<Solenoid> lightsBlue;
	static std::shared_ptr<Solenoid> pixyRinglight;
	static std::shared_ptr<Solenoid> rearRingLight;

	static std::shared_ptr<PowerDistributionPanel> powerDistributionPanel;

	static void init();
};
#endif
