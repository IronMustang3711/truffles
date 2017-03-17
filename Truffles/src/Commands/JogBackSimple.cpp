#include "JogBackSimple.h"
#include "../Robot.h"
JogBackSimple::JogBackSimple() : Command("jog back(simple)",0.2) {
	  Requires(Robot::chassis.get());

}

void JogBackSimple::Initialize() {
	Robot::chassis->zeroEncoders();


}

// Called repeatedly when this Command is scheduled to run
void JogBackSimple::Execute() {
	Robot::chassis->AutoDrive(-0.3,0);

}

bool JogBackSimple::IsFinished() {
	return IsTimedOut() || Robot::chassis->getLeftRearPosition() < - 0.5;
}

void JogBackSimple::End() {
	Robot::chassis->stop();
}

