#include "JogBackCommand.h"
#include "../Robot.h"
JogBackCommand::JogBackCommand() :
		Command("jog back", 0.2), targetRotations(-0.5), pid { 0.4, 0.1, 0, 0.1,
				this, this, 0.01 } {
	Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void JogBackCommand::Initialize() {
	pid.SetSetpoint(targetRotations);
	Robot::chassis->zeroEncoders();
	initialEncoder = encoderValue();
	pid.SetInputRange(targetRotations,initialEncoder);
	pid.SetOutputRange(-0.4, 0.4);
	pid.SetPercentTolerance(10);
	pid.SetToleranceBuffer(3);
	pid.SetSetpoint(targetRotations);
	pid.Enable();
}

// Called repeatedly when this Command is scheduled to run
void JogBackCommand::Execute() {
	SmartDashboard::PutNumber("jog: error",pid.GetError());

}

// Make this return true when this Command no longer needs to run execute()
bool JogBackCommand::IsFinished() {
	return pid.OnTarget() || IsTimedOut();
}

// Called once after isFinished returns true
void JogBackCommand::End() {
	pid.Disable();
	Robot::chassis->stop();
}

double JogBackCommand::encoderValue() {
	return Robot::chassis->getLeftRearPosition();
}

void JogBackCommand::PIDWrite(double output) {
	 SmartDashboard::PutNumber("jog: out",output);
	Robot::chassis->AutoDrive(output, 0);
}

double JogBackCommand::PIDGet() {
	return encoderValue() - initialEncoder;
}
