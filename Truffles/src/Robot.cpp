#include "Robot.h"


#include "commands/auto/Noop.h"
#include "commands/auto/DriveStraight.h"
#include "vision/Vision.h"
#include "commands/auto/AutonomousCommandFactory.h"

std::shared_ptr<Chassis> Robot::chassis;
std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Hexapus> Robot::hexapus;
std::shared_ptr<Intake> Robot::intake;
std::shared_ptr<Winch> Robot::winch;
std::shared_ptr<GearCatch> Robot::gearCatch;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<Lights> Robot::lights;

Image *cameraFrame;


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

	AutonomousCommandFactory::setupChooser(chooser);
	SmartDashboard::PutData("auto modes", &chooser);

	//autonomousCommand.reset(new Noop());

	CameraServer::GetInstance()->StartAutomaticCapture().SetResolution(320, 240);

	// std::thread visionThread(vision);
//	  visionThread.detach();

}

//void Robot::vision3(){
//	cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
//	cs::CvSource outputStream = CameraServer::GetInstance()->PutVideo("vision",
//			320, 240);
//	VerticalLinePipeline pipe;
//	cv::Mat src;
//	for(;;){
//	if (cvSink.GrabFrame(src) == 0) {
//		// Send the output the error.
//		outputStream.NotifyError(cvSink.GetError());
//		// skip the rest of the current iteration
//		continue;
//	}
//	pipe.Process(src);
////	cv::rectangle(src, cv::Point(5, 5), cv::Point(100, 100),
////			cv::Scalar(255, 0, 0));
//	outputStream.PutFrame(src);
//	}
//}
//
//void Robot::vision2(){
//	auto outVideo = CameraServer::GetInstance()->PutVideo("machine vision",320,240);
//	auto myCallback = [](VerticalLinePipeline& pipe){
//		//TODO: replace with something useful!
//	};
//	VisionRunner<VerticalLinePipeline> runner(outVideo,new VerticalLinePipeline(),myCallback);
//
//	runner.RunForever(); //I assume that this blocks, but one never knows with wpilib code.
//}
//
//void Robot::vision() {
//	cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
//	camera.SetResolution(640, 480);
//	cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
//	cs::CvSource outputStream = CameraServer::GetInstance()->PutVideo("corners",
//			320, 240);
//
//	cv::Mat src;
//	cv::Mat src_gray;
//
//	srand(123);
//
//	//	  auto detector = cv::FastFeatureDetector::create();
//	//	  std::vector<cv::KeyPoint> keys;
//
//	while (true) {
//		if (cvSink.GrabFrame(src) == 0) {
//			// Send the output the error.
//			outputStream.NotifyError(cvSink.GetError());
//			// skip the rest of the current iteration
//			continue;
//		}
//		cv::cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);
//		//		keys.clear();
//		//		detector->detect(src_gra, keys);
//
//		std::vector<cv::Point2f> corners;
//		cv::Mat copy;
//		copy = src.clone();
//
//		double qualityLevel = 0.01;
//		double minDistance = 10;
//		int blockSize = 3;
//		bool useHarrisDetector = false;
//		int maxCorners = 20;
//		double k = 0.04;
//
//		cv::goodFeaturesToTrack(src_gray, corners, maxCorners, qualityLevel,
//				minDistance, cv::Mat(), blockSize, useHarrisDetector, k);
//		int r = 4;
//		for (size_t i = 0; i < corners.size(); i++) {
//			cv::circle(copy, corners[i], r,
//					cv::Scalar(rand() * 255, rand() * 255.0, rand() * 255), -1,
//					8, 0);
//		}
//
//		outputStream.PutFrame(copy);
//	}
//}

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

//	std::thread visionThread(vision3);
//	  visionThread.detach();
	Vision::getInstance().start();
}

void Robot::AutonomousPeriodic() {
	lights->perimeterGreen.toggle(); //TODO this is probably annoying
	Scheduler::GetInstance()->Run();
	TrackPegSliderPeriodic();
}

void Robot::TeleopInit() {
	autonomousDidFinish();
	lights->perimeterGreen.setOn(false);
	RobotMap::ahrs->ZeroYaw();
	chassis->zeroEncoders();
	updateAllianceColor();
}

void Robot::TrackPegSliderPeriodic() {
	// TODO: Put camera image into frame here!
	trackPegSlider();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	TrackPegSliderPeriodic();
	dashboardUpdate();
}

void Robot::TestPeriodic() {
	updateAllianceColor();
	lw->Run();
}

void Robot::autonomousDidFinish() {
	updateAllianceColor();
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();
	lights->perimeterGreen.setOn(false);
	RobotMap::ahrs->ZeroYaw();
	chassis->zeroEncoders();
	Vision::getInstance().stop();
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

void Robot::trackPegSlider() {
	int width = 320;
	int height = 240;
	int histogram[width];
	char sourceImage[height][width][4]; // TODO: Source image from camera should go in here!
	char buffer[height][width][3];  // Our buffer doesn't need alpha channel

	// Copy image into our array
	char *arrayP;
	arrayP = (char*)imaqImageToArray(cameraFrame, IMAQ_NO_RECT, NULL, NULL);
	memcpy(sourceImage, arrayP, sizeof(sourceImage));

	// Edge detection enhanced for vertical lines
	float matrix[3][3] = { { -1, -1, -1 },
	                       { -1,  9, -1 },
	                       { -1, -1, -1 } };

	for (int x = 1; x < width - 1; x++) {
		for (int y = 1; y < height - 1; y++) {
			int sum = 0;
			for (int my = -1; my <= 1; my++) {
				for (int mx = -1; mx <= 1; mx++) {
					int pos = (y + my) * width + (x + mx);
					float val = sourceImage[y][x][0] + sourceImage[y][x][1] + sourceImage[y][x][2];
					if (val > 180 * 3) {
						sum += matrix[my + 1][mx + 1] * val;
					}
				}
			}
			buffer[y][x][0] = sum / 3.0;
			buffer[y][x][1] = sum / 3.0;
			buffer[y][x][2] = sum / 3.0;
		}
	}

	// Clear our histogram
	memset(histogram, 0, sizeof(histogram));

	// Generate histogram
	int maxHistVal = 0;
	for (int y = height / 2 - 30 - 20; y < height / 2 + 10 + 20; y++) {
		for (int x = 0; x < width; x++) {
			int r = buffer[y][x][0];
			int g = buffer[y][x][1];
			int b = buffer[y][x][2];

			int sum = r + g + b;
			if (sum > 10 * 3) {
				histogram[x] += sum;
			}
		}
	}

	// Figure out what the max histogram value was
	int maxHistVal = 0;
	for (int x = 0; x < width; x++) {
		if (histogram[x] > maxHistVal) {
			maxHistVal = histogram[x];
		}
	}

	// Find right and left side
	int leftPos = -1;
	for (int x = 0; x < width; x++) {
		if ((float) histogram[x] / maxHistVal * 20 > 15 && leftPos == -1) {
			leftPos = x;
		}
	}
	int rightPos = -1;
	for (int x = width - 1; x > 0; x--) {
		if ((float) histogram[x] / maxHistVal * 20 > 15 && rightPos == -1) {
			rightPos = x;
		}
	}

	Robot::chassis->pegSliderLeft = leftPos;
	Robot::chassis->pegSliderRight = rightPos;
}

START_ROBOT_CLASS(Robot)
