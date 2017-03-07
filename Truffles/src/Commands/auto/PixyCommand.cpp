/*
 * PixyCommand.cpp
 *
 *  Created on: 6 Mar 2017
 *      Author: steffen
 */

#include <Commands/auto/PixyCommand.h>

PixyCommand::PixyCommand(): Command() {
	pixy = new Pixy(I2C::Port::kOnboard, PIXY_I2C_ADDR);
}

PixyCommand::~PixyCommand() {
	// TODO Auto-generated destructor stub
}

