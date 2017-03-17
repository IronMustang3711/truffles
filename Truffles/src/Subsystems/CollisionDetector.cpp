#include "CollisionDetector.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "DriverStation.h"
#include "Commands/Command.h"
#include "../Robot.h"
#include <string>
using namespace frc;

class DashboardCollisionNotifier: public frc::Command {
public:
	DashboardCollisionNotifier() :
			Command("dashboard collision notifier") {
		Requires(Robot::collisionDetector.get());
	}
	bool IsFinished() override {
		return false;
	}

	void Execute() override {
		SmartDashboard::PutBoolean("collision detected: ",
				Robot::collisionDetector->impactDetected());
		SmartDashboard::PutNumber("max jerk(x)",
				Robot::collisionDetector->maxJerkX);
		SmartDashboard::PutNumber("max jerk(y)",
				Robot::collisionDetector->maxJerkY);
	}

};

void CollisionDetector::InitDefaultCommand() {
	SetDefaultCommand(new DashboardCollisionNotifier());
}

CollisionDetector::CollisionDetector() :
		Subsystem("Collision Detector"), ahrs(RobotMap::ahrs.get()) {
	start();

}

void CollisionDetector::resetDetector() {
	last_world_linear_accel_x = 0;
	last_world_linear_accel_y = 0;
	collisionDetected = false;
}
static const double COLLISION_THRESHOLD_DELTA_G = 0.2;

bool CollisionDetector::impactDetected() {
	return collisionDetected.load();
}

void CollisionDetector::stop() {
	notifier.Stop();
}

void CollisionDetector::start() {
	resetDetector();
	notifier.StartPeriodic(0.01);
}

void CollisionDetector::update() {
	double curr_world_linear_accel_x = ahrs->GetWorldLinearAccelX();
	double currentJerkX = curr_world_linear_accel_x - last_world_linear_accel_x;
	last_world_linear_accel_x = curr_world_linear_accel_x;
	double curr_world_linear_accel_y = ahrs->GetWorldLinearAccelY();
	double currentJerkY = curr_world_linear_accel_y - last_world_linear_accel_y;
	last_world_linear_accel_y = curr_world_linear_accel_y;
	if (fabs(currentJerkX) > maxJerkX) {
		maxJerkX = fabs(currentJerkX);
		std::string msg;
		printf("jerk x: %f", maxJerkX);

	}
	if (fabs(currentJerkY) > maxJerkY) {
		maxJerkY = fabs(currentJerkY);
		printf("jerk y: %f", maxJerkY);
	}
	if ((fabs(currentJerkX) > COLLISION_THRESHOLD_DELTA_G)
			|| (fabs(currentJerkY) > COLLISION_THRESHOLD_DELTA_G)) {
		collisionDetected = true;
		DriverStation::ReportError("collision detected!");
	}

}

