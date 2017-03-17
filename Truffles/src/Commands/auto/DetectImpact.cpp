#include "DetectImpact.h"

DetectImpact::DetectImpact() : Command("Detect Impact"), ahrs(RobotMap::ahrs.get()) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void DetectImpact::Initialize() {
	last_world_linear_accel_x = 0;
	last_world_linear_accel_y = 0;
	collisionDetected = false;

}

static const double COLLISION_THRESHOLD_DELTA_G = 0.5;

// Called repeatedly when this Command is scheduled to run
void DetectImpact::Execute() {
	  double curr_world_linear_accel_x = ahrs->GetWorldLinearAccelX();
	            double currentJerkX = curr_world_linear_accel_x - last_world_linear_accel_x;
	            last_world_linear_accel_x = curr_world_linear_accel_x;
	            double curr_world_linear_accel_y = ahrs->GetWorldLinearAccelY();
	            double currentJerkY = curr_world_linear_accel_y - last_world_linear_accel_y;
	            last_world_linear_accel_y = curr_world_linear_accel_y;

	            if ( ( fabs(currentJerkX) > COLLISION_THRESHOLD_DELTA_G ) ||
	                 ( fabs(currentJerkY) > COLLISION_THRESHOLD_DELTA_G) ) {
	                collisionDetected = true;
	            }
	            SmartDashboard::PutBoolean(  "CollisionDetected", collisionDetected);



}

// Make this return true when this Command no longer needs to run execute()
bool DetectImpact::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DetectImpact::End() {

}


