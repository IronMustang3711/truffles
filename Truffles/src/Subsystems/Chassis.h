// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef CHASSIS_H
#define CHASSIS_H

#include <CANTalon.h>
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Chassis: public Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<CANTalon> leftFront;
	std::shared_ptr<CANTalon> leftRear;
	std::shared_ptr<CANTalon> rightFront;
	std::shared_ptr<CANTalon> rightRear;
	std::shared_ptr<RobotDrive> drive;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
public:
	Chassis();
	void InitDefaultCommand();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	/**
	 * delegates to MecanumDrive_Cartesian
	 * @param stickPosition
	 * @param gyroAngle
	 */
	void MecanumDrive(std::shared_ptr<Joystick>stickPosition,double gyroAngle = 0.0);
	void AutoDrive (float fwdSpeed, float rotateSpeed);
    void MecanumDrive_Cartesian(double x, double y, double rotation,
                                double gyroAngle = 0.0);


    double getRightFrontCurrent();
    double getRightRearCurrent();
    double getLeftFrontCurrent();
    double getLeftRearCurrent();

    void zeroEncoders();

    CANTalon* getTalons();


	void dashboardTelemetry();
};

#endif
