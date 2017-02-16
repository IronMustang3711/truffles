// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Robot.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<Chassis> Robot::chassis;
std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Intake> Robot::intake;
std::shared_ptr<Winch> Robot::winch;
std::shared_ptr<GearCatch> Robot::gearCatch;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    chassis.reset(new Chassis());
    shooter.reset(new Shooter());
    intake.reset(new Intake());
    winch.reset(new Winch());
    gearCatch.reset(new GearCatch());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());

	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	//autonomousCommand.reset(new AutonomousCommand());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

	CameraServer::GetInstance()->StartAutomaticCapture();

  }

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
//	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
    RobotMap::ahrs->ZeroYaw();
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	dashboardUpdate();
}

void Robot::TestPeriodic() {
	lw->Run();
}


void Robot::dashboardUpdate(){
    auto ahrs = RobotMap::ahrs.get();
	SmartDashboard::PutData("pdp",RobotMap::powerDistributionPanel.get());

    SmartDashboard::PutData("ahrs",RobotMap::ahrs.get());
   // SmartDashboard::PutBoolean( "IMU_Connected",        ahrs->IsConnected());
    SmartDashboard::PutNumber(  "IMU_Yaw",              ahrs->GetYaw());
    SmartDashboard::PutNumber(  "IMU_Pitch",            ahrs->GetPitch());
    SmartDashboard::PutNumber(  "IMU_Roll",             ahrs->GetRoll());
    //SmartDashboard::PutNumber(  "IMU_CompassHeading",   ahrs->GetCompassHeading());
    //SmartDashboard::PutNumber(  "IMU_Update_Count",     ahrs->GetUpdateCount());
    //SmartDashboard::PutNumber(  "IMU_Byte_Count",       ahrs->GetByteCount());
    //SmartDashboard::PutNumber(  "IMU_Timestamp",        ahrs->GetLastSensorTimestamp());

    /* These functions are compatible w/the WPI Gyro Class */
    SmartDashboard::PutNumber(  "IMU_TotalYaw",         ahrs->GetAngle());
    SmartDashboard::PutNumber(  "IMU_YawRateDPS",       ahrs->GetRate());

   // SmartDashboard::PutNumber(  "IMU_Accel_X",          ahrs->GetWorldLinearAccelX());
    //SmartDashboard::PutNumber(  "IMU_Accel_Y",          ahrs->GetWorldLinearAccelY());
    //SmartDashboard::PutBoolean( "IMU_IsMoving",         ahrs->IsMoving());
   // SmartDashboard::PutNumber(  "IMU_Temp_C",           ahrs->GetTempC());
    //SmartDashboard::PutBoolean( "IMU_IsCalibrating",    ahrs->IsCalibrating());

    SmartDashboard::PutNumber(  "Velocity_X",           ahrs->GetVelocityX() );
    SmartDashboard::PutNumber(  "Velocity_Y",           ahrs->GetVelocityY() );
    SmartDashboard::PutNumber(  "Displacement_X",       ahrs->GetDisplacementX() );
    SmartDashboard::PutNumber(  "Displacement_Y",       ahrs->GetDisplacementY() );

    /* Display Raw Gyro/Accelerometer/Magnetometer Values                       */
    /* NOTE:  These values are not normally necessary, but are made available   */
    /* for advanced users.  Before using this data, please consider whether     */
    /* the processed data (see above) will suit your needs.                     */

    SmartDashboard::PutNumber(  "RawGyro_X",            ahrs->GetRawGyroX());
    SmartDashboard::PutNumber(  "RawGyro_Y",            ahrs->GetRawGyroY());
    SmartDashboard::PutNumber(  "RawGyro_Z",            ahrs->GetRawGyroZ());
//    SmartDashboard::PutNumber(  "RawAccel_X",           ahrs->GetRawAccelX());
//    SmartDashboard::PutNumber(  "RawAccel_Y",           ahrs->GetRawAccelY());
//    SmartDashboard::PutNumber(  "RawAccel_Z",           ahrs->GetRawAccelZ());
//    SmartDashboard::PutNumber(  "RawMag_X",             ahrs->GetRawMagX());
//    SmartDashboard::PutNumber(  "RawMag_Y",             ahrs->GetRawMagY());
//    SmartDashboard::PutNumber(  "RawMag_Z",             ahrs->GetRawMagZ());
//    SmartDashboard::PutNumber(  "IMU_Temp_C",           ahrs->GetTempC());
//    /* Omnimount Yaw Axis Information                                           */
    /* For more info, see http://navx-mxp.kauailabs.com/installation/omnimount  */
    AHRS::BoardYawAxis yaw_axis = ahrs->GetBoardYawAxis();
    SmartDashboard::PutString(  "YawAxisDirection",     yaw_axis.up ? "Up" : "Down" );
    SmartDashboard::PutNumber(  "YawAxis",              yaw_axis.board_axis );

    /* Sensor Board Information                                                 */
    SmartDashboard::PutString(  "FirmwareVersion",      ahrs->GetFirmwareVersion());

    /* Quaternion Data                                                          */
    /* Quaternions are fascinating, and are the most compact representation of  */
    /* orientation data.  All of the Yaw, Pitch and Roll Values can be derived  */
    /* from the Quaternions.  If interested in motion processing, knowledge of  */
    /* Quaternions is highly recommended.                                       */
    SmartDashboard::PutNumber(  "QuaternionW",          ahrs->GetQuaternionW());
    SmartDashboard::PutNumber(  "QuaternionX",          ahrs->GetQuaternionX());
    SmartDashboard::PutNumber(  "QuaternionY",          ahrs->GetQuaternionY());
    SmartDashboard::PutNumber(  "QuaternionZ",          ahrs->GetQuaternionZ());

}
START_ROBOT_CLASS(Robot)

