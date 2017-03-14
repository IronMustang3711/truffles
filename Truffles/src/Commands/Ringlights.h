#ifndef Ringlights_H
#define Ringlights_H

#include "Commands/InstantCommand.h"

class Ringlights : public InstantCommand {
public:
	Ringlights();
	void Execute();

};

#endif  // Ringlights_H
