// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "Shooter.h"
#include "../RobotMap.h"
#include "../Commands/RunShooter.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Shooter::Shooter() : Subsystem("Shooter") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    shooterController = RobotMap::shooterController;
    hexapusController = RobotMap::hexapusController;

    initShooter();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    shooterRunning = false;
}

void Shooter::initShooter() {

    shooterController->SetFeedbackDevice(CANTalon::QuadEncoder);
    shooterController->ConfigEncoderCodesPerRev(20);
    shooterController->SetSensorDirection(true);
    shooterController->SetPosition(0);
    shooterController->SetControlMode(CANSpeedController::kSpeed);
    shooterController->SetClosedLoopOutputDirection(false);
    // Nominal Closed-Loop Output: Promotes the minimal or weakest motor-output
    // during closed-loop.
    shooterController->ConfigNominalOutputVoltage(+0., -0.0);
    shooterController->ConfigPeakOutputVoltage(12.0, -12.0);
    /* set the allowable closed-loop error,
     * Closed-Loop output will be neutral within this range.
     * See Table in Section 17.2.1 for native units per rotation.
     */
    shooterController->SetAllowableClosedLoopErr(0); /* always servo */
    shooterController->SetF(1.45);
    shooterController->SetP(1.0);
    shooterController->SetI(0.0);
    shooterController->SetD(0.0);
    shooterController->SetCloseLoopRampRate(0.0);
}

void Shooter::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

    SetDefaultCommand(new RunShooter());
}

void Shooter::runHexapusMotor(double speed) {
    SmartDashboard::PutNumber("Shooter:HexapusMotor:input", speed);

    hexapusController->Set(-speed);
}

/**
 * [0,0.1) -> [0,3000)
 * [0.1,1.0]->[3000,4500]
 */
// TODO update numbers for new max rpm, test to see if this provides better
// control than log scaling.
double remapSliderValue(double input) {
    return input < 0.1 ? input * 30000.0 : input * 1666.7 + 2833.3;
}


/**
 * speed in [0,1]
 */
void Shooter::runShooterMotor(double input) {


    // double target = 5300.0 * log10(9.0 * input + 1.0);
    double target = remapSliderValue(input);

    shooterController->Set(target);


    SmartDashboard::PutNumber("shooter:target", target);
    SmartDashboard::PutNumber("shooter:input", input);
    SmartDashboard::PutNumber("shooter:speed", shooterController->GetSpeed());
    SmartDashboard::PutNumber("Shooter:error", shooterController->GetClosedLoopError());

}

bool Shooter::isHexapusJammed() {
    return getHexapusCurrent() >= 10.0;
}

double Shooter::getHexapusCurrent() {
    return RobotMap::powerDistributionPanel->GetCurrent(2);
}

