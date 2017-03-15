//
// Created by Jason Markham on 2/20/17.
//

#ifndef TRUFFLES_HEXAPUSCOMMAND_H
#define TRUFFLES_HEXAPUSCOMMAND_H
#include <Commands/Command.h>
#include <Commands/InstantCommand.h>
#include <Timer.h>
#include "SimpleCommand.h"
#include <string>
class RunHexapusCommand: public SimpleCommand {
public:
	RunHexapusCommand();
	enum class State {
		INITIAL_OFF, WAITING_FOR_SHOOTER, RUNNING, UNJAM
	};
	State getState();

protected:
	virtual void Initialize() override;
	virtual void Execute() override;
	virtual void End() override;
	void transition(State newState);

	static std::string StateName(State state);

private:
	Timer unjamTimer { };
	State state { State::INITIAL_OFF };
	int jamCount = 0;
	int runCount = 0;
};

class UnjamHexapus: public SimpleCommand {
public:
	UnjamHexapus(Command* whenFinished);
	virtual void Execute() override;
	virtual void End() override;
	Command* nextCommand;
};
class StopHexapus: public InstantCommand {
public:
	StopHexapus();
	virtual void Execute() override;
};



#endif  // TRUFFLES_HEXAPUSCOMMAND_H
