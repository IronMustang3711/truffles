//
// Created by Jason Markham on 2/14/17.
//

#ifndef TRUFFLES_GEARCATCH_H
#define TRUFFLES_GEARCATCH_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "LinearActuator.h"
#include <bits/shared_ptr.h>

class GearCatch : public Subsystem {
    enum Position {

        ACCEPT_BALLS = 0,
        ACCEPT_GEARS,
        CHILL
    };
public:
    GearCatch();

    void moveTo(Position p);

    void moveOut();

    void chill();

   // void moveVertical();

    /**
     *
     * @param position a value between 0 and 1
     */
    void setPosition(double position);

    /**
     *
     * @return a value between 0 and 1
     */
    double getPosition();

    void InitDefaultCommand() override;

    //TODO: What did I want to do with the following methods...

    Position getState();

    bool stateTransitionComplete();


private:
    std::shared_ptr<LinearActuator> actuator1;
    std::shared_ptr<LinearActuator> actuator2;
    Position state = Position::CHILL;
    bool stateTransitionFinished = true;


};


#endif //TRUFFLES_GEARCATCH_H
