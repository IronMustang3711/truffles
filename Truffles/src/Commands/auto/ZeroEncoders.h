//
// Created by Jason Markham on 3/3/17.
//

#ifndef TRUFFLES_ZEROENCODERS_H
#define TRUFFLES_ZEROENCODERS_H

#include "commands/InstantCommand.h"
class ZeroEncoders: public InstantCommand {
protected:
	void Execute() override;
};

#endif  // TRUFFLES_ZEROENCODERS_H
