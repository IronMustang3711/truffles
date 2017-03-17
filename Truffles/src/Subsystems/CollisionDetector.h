#ifndef CollisionDetector_H
#define CollisionDetector_H

#include <Commands/Subsystem.h>
#include <Notifier.h>
#include <atomic>
#include "AHRS.h"
class CollisionDetector : public Subsystem {

private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:
	CollisionDetector();

	virtual void InitDefaultCommand() override;


	void resetDetector();

	bool impactDetected();

	void stop();
	void start();



//private:
    void update();
    Notifier notifier{&CollisionDetector::update,this};
    AHRS *ahrs;             // navX MXP
    double last_world_linear_accel_x = 0;
    double last_world_linear_accel_y = 0;
    double maxJerkX = 0;
    double maxJerkY = 0;
    std::atomic_bool collisionDetected{false};

};

#endif  // CollisionDetector_H
