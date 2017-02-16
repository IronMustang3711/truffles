//
// Created by Jason Markham on 2/14/17.
//

#ifndef TRUFFLES_GEARCATCH_H
#define TRUFFLES_GEARCATCH_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <bits/shared_ptr.h>

class GearCatch: public Subsystem {
public:
    GearCatch();

    void moveOutward();
    void moveInward();
    void moveVertical();
    void setPosition(double position);

    void InitDefaultCommand() override;

private:
    std::shared_ptr<Servo> actuator1;
    std::shared_ptr<Servo> actuator2;



};


#endif //TRUFFLES_GEARCATCH_H
