//
// Created by Jason Markham on 2/20/17.
//

#ifndef TRUFFLES_SIMPLECOMMAND_H
#define TRUFFLES_SIMPLECOMMAND_H
#include <Commands/Command.h>
//Used in Hexapus Commands
class SimpleCommand: public Command {
public:
	SimpleCommand(const std::string& name);

	SimpleCommand(const std::string& name, double timeout);

//protected:
//	void Interrupted() override;

protected:
	bool IsFinished() override;
};

#endif  // TRUFFLES_SIMPLECOMMAND_H
