/*
 * ClearSmartDashboardCommand.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: jason
 */

#include "ClearSmartDashboardCommand.h"


void ClearSmartDashboardCommand::clearSmartDashboardData(){
	for(std::string key: SmartDashboard::GetKeys()){
		if(SmartDashboard::IsPersistent(key)){
			SmartDashboard::ClearPersistent(key);
		}
		SmartDashboard::Delete(key);
	}

}
