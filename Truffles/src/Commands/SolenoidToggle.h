/*
 * SolenoidToggle.h
 *
 *  Created on: Mar 6, 2017
 *      Author: jason
 */

#ifndef SRC_SUBSYSTEMS_SOLENOIDTOGGLE_H_
#define SRC_SUBSYSTEMS_SOLENOIDTOGGLE_H_
#include "commands/InstantCommand.h"
#include <solenoid.h>
class SolenoidToggle: public InstantCommand {
public:
	SolenoidToggle(std::shared_ptr<Solenoid> solenoid, std::string name =
			"solenoid toggle");

	virtual void Execute() override;

private:
	std::shared_ptr<Solenoid> solenoid;
};

#endif /* SRC_SUBSYSTEMS_SOLENOIDTOGGLE_H_ */
