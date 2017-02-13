/*
 * ClearSmartDashboardCommand.h
 *
 *  Created on: Jan 24, 2017
 *      Author: jason
 */

#ifndef SRC_COMMANDS_CLEARSMARTDASHBOARDCOMMAND_H_
#define SRC_COMMANDS_CLEARSMARTDASHBOARDCOMMAND_H_

#include "../Robot.h"

class ClearSmartDashboardCommand : public Command{
	public:
	ClearSmartDashboardCommand() : Command("clear smart dashboard"){}

	void clearSmartDashboardData();
};

#endif /* SRC_COMMANDS_CLEARSMARTDASHBOARDCOMMAND_H_ */
