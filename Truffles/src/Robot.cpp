
#include "Robot.h"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "commands/Noop.h"
#include "commands/auto/DriveStraight.h"

std::shared_ptr<Chassis> Robot::chassis;
std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Hexapus> Robot::hexapus;
std::shared_ptr<Intake> Robot::intake;
std::shared_ptr<Winch> Robot::winch;
std::shared_ptr<GearCatch> Robot::gearCatch;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<Lights> Robot::lights;
/**
 * WARNING: changing order of initialization will probably break everything!
 */
void Robot::RobotInit() {
	RobotMap::init();
	chassis.reset(new Chassis());
	shooter.reset(new Shooter());
	hexapus.reset(new Hexapus());
	intake.reset(new Intake());
	winch.reset(new Winch());
	gearCatch.reset(new GearCatch());
	lights.reset(new Lights());

	oi.reset(new OI());

	updateAllianceColor();

	chooser.AddDefault("nothing", new Noop());
	chooser.AddObject("drive straight", new DriveStraight(2));
	SmartDashboard::PutData("auto modes",&chooser);

	//autonomousCommand.reset(new Noop());

	CameraServer::GetInstance()->StartAutomaticCapture().SetResolution(320,
			240);
	  std::thread visionThread(vision);
	  visionThread.detach();
}

// TODO see https://www.chiefdelphi.com/forums/showthread.php?threadid=156277
void Robot::vision() {
	cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
	camera.SetResolution(640, 480);
	cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
	cs::CvSource outputStream = CameraServer::GetInstance()->PutVideo("corners",
			320, 240);

	cv::Mat src;
	cv::Mat src_gray;

	srand(123);

	//	  auto detector = cv::FastFeatureDetector::create();
	//	  std::vector<cv::KeyPoint> keys;

	while (true) {
		if (cvSink.GrabFrame(src) == 0) {
			// Send the output the error.
			outputStream.NotifyError(cvSink.GetError());
			// skip the rest of the current iteration
			continue;
		}
		cv::cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);
		//		keys.clear();
		//		detector->detect(src_gra, keys);

		std::vector<cv::Point2f> corners;
		cv::Mat copy;
		copy = src.clone();

		double qualityLevel = 0.01;
		double minDistance = 10;
		int blockSize = 3;
		bool useHarrisDetector = false;
		int maxCorners = 20;
		double k = 0.04;

		cv::goodFeaturesToTrack(src_gray, corners, maxCorners, qualityLevel,
				minDistance, cv::Mat(), blockSize, useHarrisDetector, k);
		int r = 4;
		for (size_t i = 0; i < corners.size(); i++) {
			cv::circle(copy, corners[i], r,
					cv::Scalar(rand() * 255, rand() * 255.0, rand() * 255), -1,
					8, 0);
		}

		outputStream.PutFrame(copy);
	}
}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit() {
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	updateAllianceColor();
	lights->perimeterGreen.setOn(false);

	autonomousCommand.reset(chooser.GetSelected());
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousPeriodic() {
	//if we cant do autonomous, at least we can sparkle....
	lights->perimeterGreen.toggle();
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	lights->perimeterGreen.setOn(false);
	RobotMap::ahrs->ZeroYaw();
	chassis->zeroEncoders();
	updateAllianceColor();

	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	dashboardUpdate();
}

void Robot::TestPeriodic() {
	updateAllianceColor();
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
