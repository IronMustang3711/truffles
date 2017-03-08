/*
 * DelegatingPIDSource.cpp
 *
 *  Created on: Mar 7, 2017
 *      Author: jason
 */

#include <pid/DelegatingPIDSource.h>

DelegatingPIDSource::DelegatingPIDSource(PIDSourceProvider pidFunc) : provider(pidFunc) {

}
double DelegatingPIDSource::PIDGet(){
	return provider();
}
DelegatingPIDSource::~DelegatingPIDSource() {

}

