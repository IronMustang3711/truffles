/*
 * SolenoidToggle.h
 *
 *  Created on: Mar 6, 2017
 *      Author: jason
 */

#ifndef SRC_SUBSYSTEMS_SOLENOIDTOGGLE_H_
#define SRC_SUBSYSTEMS_SOLENOIDTOGGLE_H_
#include "commands/InstantCommand.h"
#include "Solenoid.h"
class SolenoidToggle : public InstantCommand {
//class Solenoid; //TODO figure out how forward declarations work in cpp
public:
	SolenoidToggle(std::shared_ptr<Solenoid>solenoid, std::string name="solenoid toggle");

	virtual void Execute() override;

private:
	std::shared_ptr<Solenoid> solenoid;

};

#endif /* SRC_SUBSYSTEMS_SOLENOIDTOGGLE_H_ */
