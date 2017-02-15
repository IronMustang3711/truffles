//
// Created by Jason Markham on 2/14/17.
//

#ifndef TRUFFLES_GEARCATCHCOMMANDS_H
#define TRUFFLES_GEARCATCHCOMMANDS_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class GearCatchCommand : public ::frc::Command {

public:
    GearCatchCommand(const std::string& name);
    virtual void Interrupted() override;

    virtual void End() override;

    virtual bool IsFinished() override;

    virtual void Initialize() override;

    long IsTimedOut() const ;
};

class GearCatchVertical : public GearCatchCommand {
public:
    GearCatchVertical();

    virtual void Execute() override;

};


class GearCatchOut : public GearCatchCommand {
public:
    GearCatchOut();


    virtual void Execute() override;


};

class GearCatchIn : public GearCatchCommand {
public:
    GearCatchIn();

    virtual void Execute() override;

};


#endif //TRUFFLES_GEARCATCHCOMMANDS_H
