//
// Created by Jason Markham on 2/20/17.
//

#ifndef TRUFFLES_TOGGLELIGHTS_H
#define TRUFFLES_TOGGLELIGHTS_H

#include "Commands/Subsystem.h"
#include "../Robot.h"


class ToggleLights : public InstantCommand {

public:
    ToggleLights();

protected:
    void Execute() override;

};


#endif //TRUFFLES_TOGGLELIGHTS_H
