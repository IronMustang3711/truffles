//
// Created by Jason Markham on 2/14/17.
//

#ifndef TRUFFLES_GEARCATCHCOMMANDS_H
#define TRUFFLES_GEARCATCHCOMMANDS_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

class GearCatchVertical : public Command {
public:
    GearCatchVertical();

    virtual void Execute() override;

    virtual void Initialize() override;

    virtual bool IsFinished() override;

    virtual void End() override;

    virtual void Interrupted() override;

};


class GearCatchOut : public Command {
public:
    GearCatchOut();


    virtual void Execute() override;

    virtual void Initialize() override;

    virtual bool IsFinished() override;

    virtual void End() override;

    virtual void Interrupted() override;


};

class GearCatchIn : public Command {
public:
    GearCatchIn();

    virtual void Execute() override;

    virtual void Initialize() override;

    virtual bool IsFinished() override;

    virtual void End() override;

    virtual void Interrupted() override;

};


#endif //TRUFFLES_GEARCATCHCOMMANDS_H
