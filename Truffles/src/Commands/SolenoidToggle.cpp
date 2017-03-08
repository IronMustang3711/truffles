/*
 * SolenoidToggle.cpp
 *
 *  Created on: Mar 6, 2017
 *      Author: jason
 */

#include "SolenoidToggle.h"
#include <commands/InstantCommand.h>
SolenoidToggle::SolenoidToggle(std::shared_ptr<Solenoid>ptr, std::string _name): InstantCommand(_name), solenoid{ptr} {
}

void SolenoidToggle::Execute(){
	solenoid->Set(!solenoid->Get());
}



