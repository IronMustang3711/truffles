#ifndef RUNWINCH_H
#define RUNWINCH_H

#include <Commands/Command.h>

class RunWinch: public Command {
public:
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

	static RunWinch* createGoUpCommand();
	static RunWinch* createHoldCommand();
	static RunWinch* createDownCommand();
	static RunWinch* createStopCommand();

protected:
	RunWinch(double speed);

private:
	double m_speed;
};

#endif
