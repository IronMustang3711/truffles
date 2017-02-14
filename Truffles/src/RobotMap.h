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
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "WPILib.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

const int ENCODER_PULSES_PER_REVOLUTION = 20;

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
class RobotMap {
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static std::shared_ptr<CANTalon> leftFrontController;
	static std::shared_ptr<CANTalon> leftRearController;
	static std::shared_ptr<CANTalon> rightFrontController;
	static std::shared_ptr<CANTalon> rightRearController;
	static std::shared_ptr<RobotDrive> chassisDrive;
	static std::shared_ptr<CANTalon> shooterController;
	static std::shared_ptr<Spark> intakeController;
	static std::shared_ptr<Spark> winchController;
	static std::shared_ptr<Spark> hexapusController;


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	static std::shared_ptr<PowerDistributionPanel> powerDistributionPanel;
	static const PowerDistributionPanel& getPowerDistributionPanel();

	static void init();
};
#endif
