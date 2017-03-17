//
// Created by Jason Markham on 2/21/17.
//

#include "Hexapus.h"
#include "../RobotMap.h"
#include <SmartDashboard/SmartDashboard.h>
using namespace frc;

Hexapus::Hexapus() :
		Subsystem("hexapus") {
	hexapusController = RobotMap::hexapusController;
	;
}

bool Hexapus::isJammed() {
	bool jam = getMotorCurrent() >= 9.5;
	return jam;
}

double Hexapus::getMotorCurrent() {
	double ret = RobotMap::powerDistributionPanel->GetCurrent(2);
	//SmartDashboard::PutNumber("hexapus current",ret);
	return ret;
}
void Hexapus::run(double speed) {
	//SmartDashboard::PutBoolean("hexapus jammed", isJammed());
	hexapusController->Set(-speed);
}
void Hexapus::run() {
	run(0.7);
}

void Hexapus::stop() {
	run(0);
}

void Hexapus::unjam() {
	run(-0.6);
}
