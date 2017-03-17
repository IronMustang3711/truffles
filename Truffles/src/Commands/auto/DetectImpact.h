#ifndef DetectImpact_H
#define DetectImpact_H

#include "WPILib.h"
#include "../../RobotMap.h"

class DetectImpact : public Command {
public:
	DetectImpact();
	void Initialize() override;
	void Execute() override;
	bool IsFinished();
	void End();

    AHRS *ahrs;             // navX MXP
    double last_world_linear_accel_x = 0;
    double last_world_linear_accel_y = 0;
    bool collisionDetected = false;
};

#endif  // DetectImpact_H
