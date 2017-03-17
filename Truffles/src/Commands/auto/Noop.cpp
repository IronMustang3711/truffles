#include "Noop.h"
#include "DriverStation.h"
#include "../../Robot.h"
Noop::Noop() :
		InstantCommand("laaame") {
	Requires(Robot::chassis.get());
}

void Noop::Execute() {
	DriverStation::ReportError("using lame auto!!!``11");
}
