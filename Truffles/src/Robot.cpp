#include "Commands/auto/SimpleDriveForward.h"
#include "Robot.h"


#include "commands/auto/Noop.h"
#include "commands/auto/DriveStraight.h"
#include "vision/Vision.h"
#include "commands/auto/AutonomousCommandFactory.h"

Robot* Robot::robot;
std::shared_ptr<Chassis> Robot::chassis;
std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Hexapus> Robot::hexapus;
std::shared_ptr<Intake> Robot::intake;
std::shared_ptr<Winch> Robot::winch;
std::shared_ptr<GearCatch> Robot::gearCatch;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<Lights> Robot::lights;
std::shared_ptr<CollisionDetector> Robot::collisionDetector;




/**
 * WARNING: changing order of initialization will probably break everything!
 */
void Robot::RobotInit() {
	robot = this;
	RobotMap::init();
	chassis.reset(new Chassis());
	shooter.reset(new Shooter());
	hexapus.reset(new Hexapus());
	intake.reset(new Intake());
	winch.reset(new Winch());
	lights.reset(new Lights());
	collisionDetector.reset(new CollisionDetector());

	oi.reset(new OI());

	updateAllianceColor();

	AutonomousCommandFactory::setupChooser(chooser);
	SmartDashboard::PutData("auto modes", &chooser);

	autonomousCommand.reset(new Noop());

	CameraServer::GetInstance()->StartAutomaticCapture().SetResolution(320,
			240);

	SmartDashboard::PutString("version:","1.0");
}



/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit() {
	lights->setRinglightsState(false);
	//DriverStation::ReportWarning("trace:Robot:DisabledInit");
}

void Robot::DisabledPeriodic() {
	//DriverStation::ReportWarning("trace:Robot:DisabledPeriodic:enter");
	Scheduler::GetInstance()->Run();
	//DriverStation::ReportWarning("trace:Robot:DisabledPeriodic:exit");

}

void Robot::AutonomousInit() {
	//DriverStation::ReportWarning("trace:Robot:AutonomousInit:enter");
	autoDidRun = true;
	updateAllianceColor();
	lights->setRinglightsState(true);
	Vision::getInstance().start();
	autonomousCommand.reset(chooser.GetSelected());
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
	Scheduler::GetInstance()->Run();

	//DriverStation::ReportWarning("trace:Robot:AutonomousInit:exit");

}

void Robot::AutonomousPeriodic() {
	lights->perimeterGreen.toggle(); //TODO this is probably annoying
	Scheduler::GetInstance()->Run();

}

void Robot::TeleopInit() {
//	DriverStation::ReportWarning("trace:Robot:TeleopInit:enter");
	if(autoDidRun) {
		Vision::getInstance().stop();
		if (autonomousCommand.get() != nullptr)
				autonomousCommand->Cancel();
	}
	updateAllianceColor();
	lights->setRinglightsState(true);
	lights->perimeterGreen.setOn(false);
	RobotMap::ahrs->ZeroYaw();
	chassis->zeroEncoders();

//	DriverStation::ReportWarning("trace:Robot:TeleopInit:exit");
}



void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	dashboardUpdate();
}

void Robot::TestPeriodic() {
	lw->Run();
}


void Robot::dashboardUpdate() {
	//SmartDashboard::PutData(hexapus.get());
	//SmartDashboard::PutData(shooter.get());
	// SmartDashboard::PutData("pdp", RobotMap::powerDistributionPanel.get());
	chassis->dashboardTelemetry();

	//    SmartDashboard::PutData(Scheduler::GetInstance());
	//    SmartDashboard::PutData(shooter.get());
	//    SmartDashboard::PutData(intake.get());
	//    SmartDashboard::PutData(gearCatch.get());
	//    SmartDashboard::PutData("ahrs",RobotMap::ahrs.get());
	////   // SmartDashboard::PutBoolean( "IMU_Connected", ahrs->IsConnected());
	//    SmartDashboard::PutNumber(  "IMU_Yaw",              ahrs->GetYaw());
	//    SmartDashboard::PutNumber(  "IMU_Pitch",            ahrs->GetPitch());
	//    SmartDashboard::PutNumber(  "IMU_Roll",             ahrs->GetRoll());
	//    //SmartDashboard::PutNumber(  "IMU_CompassHeading",
	//    ahrs->GetCompassHeading());
	//    //SmartDashboard::PutNumber(  "IMU_Update_Count",
	//    ahrs->GetUpdateCount());
	//    //SmartDashboard::PutNumber(  "IMU_Byte_Count", ahrs->GetByteCount());
	//    //SmartDashboard::PutNumber(  "IMU_Timestamp",
	//    ahrs->GetLastSensorTimestamp());
	//
	//    /* These functions are compatible w/the WPI Gyro Class */
	//    SmartDashboard::PutNumber(  "IMU_TotalYaw",         ahrs->GetAngle());
	//    SmartDashboard::PutNumber(  "IMU_YawRateDPS",       ahrs->GetRate());
	//
	//    SmartDashboard::PutNumber(  "IMU_Accel_X",
	//    ahrs->GetWorldLinearAccelX());
	//    SmartDashboard::PutNumber(  "IMU_Accel_Y",
	//    ahrs->GetWorldLinearAccelY());
	//    //SmartDashboard::PutBoolean( "IMU_IsMoving",         ahrs->IsMoving());
	//   // SmartDashboard::PutNumber(  "IMU_Temp_C",           ahrs->GetTempC());
	//    //SmartDashboard::PutBoolean( "IMU_IsCalibrating",
	//    ahrs->IsCalibrating());
	//
	//    SmartDashboard::PutNumber(  "Velocity_X",           ahrs->GetVelocityX()
	//    );
	//    SmartDashboard::PutNumber(  "Velocity_Y",           ahrs->GetVelocityY()
	//    );
	//    SmartDashboard::PutNumber(  "Displacement_X",
	//    ahrs->GetDisplacementX() );
	//    SmartDashboard::PutNumber(  "Displacement_Y",
	//    ahrs->GetDisplacementY() );

	/* Display Raw Gyro/Accelerometer/Magnetometer Values                       */
	/* NOTE:  These values are not normally necessary, but are made available   */
	/* for advanced users.  Before using this data, please consider whether     */
	/* the processed data (see above) will suit your needs.                     */

	//    SmartDashboard::PutNumber(  "RawGyro_X", ahrs->GetRawGyroX());
	//    SmartDashboard::PutNumber(  "RawGyro_Y", ahrs->GetRawGyroY());
	//    SmartDashboard::PutNumber(  "RawGyro_Z", ahrs->GetRawGyroZ());
	//    SmartDashboard::PutNumber(  "RawAccel_X", ahrs->GetRawAccelX());
	//    SmartDashboard::PutNumber(  "RawAccel_Y", ahrs->GetRawAccelY());
	//    SmartDashboard::PutNumber(  "RawAccel_Z", ahrs->GetRawAccelZ());
	//    SmartDashboard::PutNumber(  "RawMag_X",             ahrs->GetRawMagX());
	//    SmartDashboard::PutNumber(  "RawMag_Y",             ahrs->GetRawMagY());
	//    SmartDashboard::PutNumber(  "RawMag_Z",             ahrs->GetRawMagZ());
	//    SmartDashboard::PutNumber(  "IMU_Temp_C",           ahrs->GetTempC());
	//    /* Omnimount Yaw Axis Information */
	/* For more info, see http://navx-mxp.kauailabs.com/installation/omnimount  */
	//    AHRS::BoardYawAxis yaw_axis = ahrs->GetBoardYawAxis();
	//    SmartDashboard::PutString(  "YawAxisDirection",     yaw_axis.up ? "Up" :
	//    "Down" );
	//    SmartDashboard::PutNumber(  "YawAxis",              yaw_axis.board_axis
	//    );
	// TODO: Make sure firmware is up to date.
	/* Sensor Board Information                                                 */
	//  SmartDashboard::PutString(  "FirmwareVersion(Check that this is up to
	//  date!)",      ahrs->GetFirmwareVersion());
	/* Quaternion Data                                                          */
	/* Quaternions are fascinating, and are the most compact representation of  */
	/* orientation data.  All of the Yaw, Pitch and Roll Values can be derived  */
	/* from the Quaternions.  If interested in motion processing, knowledge of  */
	/* Quaternions is highly recommended.                                       */
	//    SmartDashboard::PutNumber(  "QuaternionW", ahrs->GetQuaternionW());
	//    SmartDashboard::PutNumber(  "QuaternionX", ahrs->GetQuaternionX());
	//    SmartDashboard::PutNumber(  "QuaternionY", ahrs->GetQuaternionY());
	//    SmartDashboard::PutNumber(  "QuaternionZ", ahrs->GetQuaternionZ());
}

void Robot::updateAllianceColor() {
	switch (DriverStation::GetInstance().GetAlliance()) {
	case DriverStation::kRed:
		lights->perimeterRed.setOn(true);
		lights->perimeterBlue.setOn(false);

		break;
	case DriverStation::kBlue:
		lights->perimeterRed.setOn(false);
		lights->perimeterBlue.setOn(true);

		break;
	case DriverStation::kInvalid:
		RobotMap::lightsGreen->Set(true);

		break;
	}
}



START_ROBOT_CLASS(Robot)
