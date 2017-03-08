/*
 * DelegatingPIDSource.h
 *
 *  Created on: Mar 7, 2017
 *      Author: jason
 */

#ifndef SRC_PID_DELEGATINGPIDSOURCE_H_
#define SRC_PID_DELEGATINGPIDSOURCE_H_
#include <PIDSource.h>
#include <memory>
#include <functional>
using namespace frc;

class DelegatingPIDSource : public PIDSource {
 public:
  typedef std::function<double(void)> PIDSourceProvider;

  DelegatingPIDSource(PIDSourceProvider);
  virtual ~DelegatingPIDSource();

  virtual double PIDGet() override;

 private:
  PIDSourceProvider provider;
};

#endif /* SRC_PID_DELEGATINGPIDSOURCE_H_ */
