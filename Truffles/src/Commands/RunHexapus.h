//
// Created by Jason Markham on 2/13/17.
//

#ifndef TRUFFLES_RUNHEXAPUS_H
#define TRUFFLES_RUNHEXAPUS_H
#include <Commands/Command.h>


class RunHexapus: public Command {

public:
    RunHexapus(double amt);
    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();

    void timeOut(double timeout) ;

private:
    double amt;
   // std::shared_ptr<SpeedController>motorController;
};


#endif //TRUFFLES_RUNHEXAPUS_H
