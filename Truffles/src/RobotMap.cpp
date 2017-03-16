#include "RobotMap.h"

using namespace frc;

std::shared_ptr<CANTalon> RobotMap::leftFrontController;
std::shared_ptr<CANTalon> RobotMap::leftRearController;
std::shared_ptr<CANTalon> RobotMap::rightFrontController;
std::shared_ptr<CANTalon> RobotMap::rightRearController;
std::shared_ptr<RobotDrive> RobotMap::chassisDrive;
std::shared_ptr<CANTalon> RobotMap::shooterController;
std::shared_ptr<Spark> RobotMap::intakeController;
std::shared_ptr<Spark> RobotMap::winchController;
std::shared_ptr<Spark> RobotMap::hexapusController;
//std::shared_ptr<LinearActuator> RobotMap::gearCatchActuator1;
//std::shared_ptr<LinearActuator> RobotMap::gearCatchActuator2;
std::shared_ptr<PowerDistributionPanel> RobotMap::powerDistributionPanel;

std::shared_ptr<AHRS> RobotMap::ahrs;
std::shared_ptr<Solenoid> RobotMap::lightsRed;
std::shared_ptr<Solenoid> RobotMap::lightsGreen;
std::shared_ptr<Solenoid> RobotMap::lightsBlue;

std::shared_ptr<Solenoid> RobotMap::pixyRinglight;
std::shared_ptr<Solenoid> RobotMap::rearRingLight;

void RobotMap::init() {
	//DriverStation::ReportWarning("trace:RobotMap::Init:enter");
	//(encoder count)*(gear reduction)
	const uint16_t encTicksPerRev = 360 * 4;
	LiveWindow* lw = LiveWindow::GetInstance();
	auto talonCommon =
			[](std::shared_ptr<CANTalon>t) {
				t->SetFeedbackDevice(CANTalon::QuadEncoder);
				t->SetPosition(0);
				t->ConfigLimitMode(CANSpeedController::kLimitMode_SrxDisableSwitchInputs);
			};
	leftFrontController.reset(new CANTalon(2));
	talonCommon(leftFrontController);
	leftFrontController->ConfigEncoderCodesPerRev(encTicksPerRev);
	leftFrontController->SetSensorDirection(false);
	lw->AddActuator("Chassis", "LeftFront", leftFrontController);

	leftRearController.reset(new CANTalon(5));
	talonCommon(leftRearController);
	leftRearController->ConfigEncoderCodesPerRev(encTicksPerRev);
	leftRearController->SetSensorDirection(false);
	lw->AddActuator("Chassis", "LeftRear", leftRearController);

	rightFrontController.reset(new CANTalon(1));
	talonCommon(rightFrontController);
	rightFrontController->ConfigEncoderCodesPerRev(1000);
	rightFrontController->SetSensorDirection(true);
	lw->AddActuator("Chassis", "RightFront", (rightFrontController));

	rightRearController.reset(new CANTalon(4));
	talonCommon(rightFrontController);
	rightFrontController->ConfigEncoderCodesPerRev(encTicksPerRev);
	rightFrontController->SetSensorDirection(true);
	lw->AddActuator("Chassis", "RightRear", (rightRearController));

	//gearbox ratio 4:1
	//wheelbase== 26"
	//encoder 360 : 1
	//theoretically: 1 revolution = 18.8"

	chassisDrive.reset(
			new RobotDrive(leftFrontController, leftRearController,
					rightFrontController, rightRearController));

	chassisDrive->SetSafetyEnabled(false);
	chassisDrive->SetExpiration(0.1);
	chassisDrive->SetSensitivity(0.5);
	chassisDrive->SetMaxOutput(1.0);

	chassisDrive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	chassisDrive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);

	shooterController.reset(new CANTalon(3));
	lw->AddActuator("Shooter", "ShooterMotor", shooterController);

	intakeController.reset(new Spark(2));
	lw->AddActuator("Intake", "IntakeMotor", (intakeController));

	winchController.reset(new Spark(1));  // TODO change to Talon?
	lw->AddActuator("Winch", "WinchMotor", (winchController));

	hexapusController.reset(new Spark(0));
	lw->AddActuator("Shooter", "hexopus", hexapusController);

//	gearCatchActuator1.reset(new LinearActuator(3));
//	lw->AddActuator("Gear Catch", "linear actuator 1", gearCatchActuator1);
//
//	gearCatchActuator2.reset(new LinearActuator(4));
//	lw->AddActuator("Gear Catch", "linear actuator 2", gearCatchActuator2);

	ahrs.reset(new AHRS(SPI::Port::kMXP));

	powerDistributionPanel.reset(new PowerDistributionPanel(10));
	lw->AddSensor("Robot", "power distribution", powerDistributionPanel);

	lightsRed.reset(new Solenoid(20, 0));
	lw->AddActuator("Lipstick", "red(0)", lightsRed);

	lightsGreen.reset(new Solenoid(20, 1));
	lw->AddActuator("Lipstick", "green(1)", lightsGreen);

	lightsBlue.reset(new Solenoid(20, 2));
	lw->AddActuator("Lipstick", "blue(2)", lightsBlue);

	pixyRinglight.reset(new Solenoid(20, 3));
	lw->AddActuator("ringlight", "pixy", pixyRinglight);

	rearRingLight.reset(new Solenoid(20, 4));
	lw->AddActuator("ringlight", "rear cam", rearRingLight);
	//DriverStation::ReportWarning("trace:RobotMap::Init:exit");

}
