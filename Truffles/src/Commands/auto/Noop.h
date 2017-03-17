#ifndef Noop_H
#define Noop_H

#include <Commands/PrintCommand.h>

class Noop: public InstantCommand {
public:
	Noop();
	virtual void Execute() override;

};

#endif  // Noop_H
