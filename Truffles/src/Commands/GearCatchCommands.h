//
// Created by Jason Markham on 2/14/17.
//

#ifndef TRUFFLES_GEARCATCHCOMMANDS_H
#define TRUFFLES_GEARCATCHCOMMANDS_H

#include "../Robot.h"
#include <Commands/Command.h>

class GearCatchCommand: public InstantCommand {
public:
	GearCatchCommand(const std::string& name);
	std::shared_ptr<GearCatch> gearCatch = Robot::gearCatch;
};

class GearCatchOut: public GearCatchCommand {
public:
	GearCatchOut();

	virtual void Execute() override;
};

class GearCatchIn: public GearCatchCommand {
public:
	GearCatchIn();

	virtual void Execute() override;
};

class GearCatchInUnpowered: public GearCatchCommand {
public:
	GearCatchInUnpowered();

	virtual void Execute() override;
};

class GearCatchToggle: public InstantCommand {
public:
	GearCatchToggle();

	virtual void Execute() override;

	void setCurrentCommand(GearCatchCommand* cmd);

protected:
	void changeCommand();

private:
	GearCatchIn catchIn { };
	GearCatchOut catchOut { };
	Command* currentCommand;
};
#endif  // TRUFFLES_GEARCATCHCOMMANDS_H
