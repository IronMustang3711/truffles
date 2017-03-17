#include "CollisionDetector.h"
#include "../RobotMap.h"

CollisionDetector::CollisionDetector() :
		Subsystem("ExampleSubsystem"), ahrs(RobotMap::ahrs.get()) {
	start();

}

void CollisionDetector::resetDetector() {
	last_world_linear_accel_x = 0;
	last_world_linear_accel_y = 0;
	collisionDetected = false;
}
static const double COLLISION_THRESHOLD_DELTA_G = 0.5;

bool CollisionDetector::impactDetected() {
	return collisionDetected.load();
}

void CollisionDetector::stop() {
	notifier.StartPeriodic(0.01);
}

void CollisionDetector::start() {
	resetDetector();
	notifier.Stop();
}

void CollisionDetector::update() {
	double curr_world_linear_accel_x = ahrs->GetWorldLinearAccelX();
	double currentJerkX = curr_world_linear_accel_x - last_world_linear_accel_x;
	last_world_linear_accel_x = curr_world_linear_accel_x;
	double curr_world_linear_accel_y = ahrs->GetWorldLinearAccelY();
	double currentJerkY = curr_world_linear_accel_y - last_world_linear_accel_y;
	last_world_linear_accel_y = curr_world_linear_accel_y;

	if ((fabs(currentJerkX) > COLLISION_THRESHOLD_DELTA_G)
			|| (fabs(currentJerkY) > COLLISION_THRESHOLD_DELTA_G)) {
		collisionDetected = true;
	}
	SmartDashboard::PutBoolean("CollisionDetected", collisionDetected);

}
// Put methods for controlling this subsystem
// here. Call these from Commands.
