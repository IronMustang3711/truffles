#include "Shooter.h"
#include "../RobotMap.h"
#include <PIDSource.h>
#include <memory>
#include <functional>
#include "../PIDStuff.h"
using namespace frc;

Shooter::Shooter() :
		Subsystem("Shooter"), shooterController(RobotMap::shooterController), errorFilter(
				LinearDigitalFilter::SinglePoleIIR(
						std::make_shared<utils::PIDSourceAdapter>(
								std::bind(&CANTalon::GetClosedLoopError,
										RobotMap::shooterController)), 1.0,
						5.0)), setpointUpdateTimer { }

{
	initShooter();
}

double map(double in, double inputMin, double inputMax, double outputMin,
		double outputMax) {
	return outputMin
			+ (outputMax - outputMin)
					* ((in - inputMin) / (inputMax - inputMin));
}

void Shooter::initShooter() {
	shooterController->SetFeedbackDevice(CANTalon::QuadEncoder);
	shooterController->ConfigEncoderCodesPerRev(20);
	shooterController->SetSensorDirection(true);
	shooterController->SetPosition(0);
	shooterController->SetControlMode(CANSpeedController::ControlMode::kSpeed);
	shooterController->SetClosedLoopOutputDirection(false);
	shooterController->ConfigNominalOutputVoltage(+1.0, -0.0);
	shooterController->ConfigPeakOutputVoltage(12.0, 0.0);
	shooterController->SetAllowableClosedLoopErr(0); /* always servo */
	shooterController->SetF(1.45);
	shooterController->SetP(1.0);
	shooterController->SetI(0.0);
	shooterController->SetD(0.0);
	shooterController->SetCloseLoopRampRate(0.0);
	//TODO: Shooter error is currently converging at ~24

}

void Shooter::InitDefaultCommand() {
}

Shooter::State Shooter::getState() {
	return state;
}

bool Shooter::isOff(double requestedSpeed) {
	return requestedSpeed == 0.0 || requestedSpeed == 10.0;
}

bool Shooter::isShooting() {
	return getClosedLoopError() - prevClosedLoopError > 50.0
			&& !setpointRecentlyChanged();
}
bool Shooter::setpointRecentlyChanged() {
	double t = setpointUpdateTimer.Get();
	if (t > 0.5) {
		setpointUpdateTimer.Stop();
		setpointUpdateTimer.Reset();
	}
	return t != 0 && t < 0.5;
}

void Shooter::run(double speed) {
	double sp = getSetPoint();
	double vel = getVelocity();
	double err = getClosedLoopError();
	double out = getOutput();

	if (isOff(speed)) {
		transition(OFF);
	}
	if (sp != prevSetPoint) {
		setpointUpdateTimer.Reset();
		setpointUpdateTimer.Start();
	}
	switch (state) {
	case OFF:
		if (!isOff(speed)) {
			transition(INIT);
		}
		break;

	case INIT:
		if (std::abs(prevClosedLoopError - err) <= 1.) {
			transition(STEADY); // error not changing much, transition to steady
		} else if (isShooting()) {
			transition(SHOOT); // large increase in error, not caused by change in
							   // setpoint
		} else {
			// still initializing
		}
		break;

	case SHOOT:
		if (std::abs(prevVelocity - vel < 10)
				|| std::abs(prevClosedLoopError - err) < 5.0) {
			// deceleration is over
			// TODO keep track of acceleration!
			transition(BANG_BANG);
		}
		break;

	case BANG_BANG:
		if (std::abs(prevClosedLoopError - err) <= 1.) {
			transition(STEADY);
		} else if (err - prevClosedLoopError > 20.0
				&& !setpointRecentlyChanged()) {
			transition(SHOOT);
		}
		break;

	case STEADY:
		if (isShooting()) {
			transition(SHOOT);
		}
		break;
	}
	shooterController->Set(speed);
	prevSetPoint = sp;
	prevVelocity = vel;
	prevClosedLoopError = err;
	prevOutput = out;
}

void Shooter::runShooterMotor(double input) {
	double target =
			input < 0.1 ?
					(10 + 31900.0 * input) :
					map(input, 0.1, 1.0, 3200.0, 4200.0);

	run(target);

	// shooterController->Set(target);

	SmartDashboard::PutString("shooter:state", StateName(state));
	SmartDashboard::PutNumber("shooter:output", prevOutput);
	SmartDashboard::PutNumber("shooter:target", target);
	// SmartDashboard::PutNumber("shooter:input", input);
	SmartDashboard::PutNumber("shooter:speed", prevVelocity);
	SmartDashboard::PutNumber("Shooter:error", prevClosedLoopError);

	//  GetTable()->PutNumber("setpoint", prevOutput);
	//  GetTable()->PutNumber("velocity", target);
	//  GetTable()->PutNumber("error", prevClosedLoopError);
	//  GetTable()->PutNumber("error(lowpass)", errorFilter.Get());
	//  GetTable()->PutNumber("output", prevOutput);
}

double Shooter::getSetPoint() {
	return shooterController->GetSetpoint();
}

double Shooter::getVelocity() {
	return shooterController->GetSpeed();
}

int Shooter::getClosedLoopError() {
	// return errorFilter.Get();
	return shooterController->GetClosedLoopError();
}

double Shooter::getOutput() {
	return shooterController->GetOutputVoltage()
			/ shooterController->GetBusVoltage();
}

std::string Shooter::StateName(Shooter::State s) {
	switch (s) {
	case OFF:
		return "OFF";
	case INIT:
		return "INIT";
	case SHOOT:
		return "SHOOT";
	case BANG_BANG:
		return "BANG_BANG";
	case STEADY:
		return "STEADY";
	}
	return "butts";
}

void Shooter::transition(Shooter::State newState) {
	if (newState == OFF) {
		shooterController->StopMotor();
	} else if (newState == BANG_BANG) {
		shooterController->SetD(0);
	} else if (newState == INIT && state == OFF) {
		initShooter();
	}

	if (state == BANG_BANG) {
		shooterController->SetD(100.0);
	}

	// GetTable()->PutString("state", StateName(newState));

	state = newState;
}

void Shooter::stop() {
	transition(OFF);
}

// void Shooter::InitTable(std::shared_ptr<ITable> subtable) {
//  subtable->PutString("state", StateName(state));
//  subtable->PutNumber("setpoint", 0);
//  subtable->PutNumber("target", 0);
//  subtable->PutNumber("velocity", 0);
//  subtable->PutNumber("error", 0);
//  subtable->PutNumber("error(lowpass)", 0);
//  subtable->PutNumber("output", 0);
//}
