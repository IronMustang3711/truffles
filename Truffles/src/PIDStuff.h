/*
 * PIDStuff.h
 *
 *  Created on: Mar 8, 2017
 *      Author: jason
 */

#ifndef SRC_PIDSTUFF_H_
#define SRC_PIDSTUFF_H_
#include <PIDSource.h>
#include <PIDOutput.h>
#include <PIDController.h>
#include <functional>
namespace utils {

typedef std::function<double(void)> PIDSourceProvider;
typedef std::function<void(double)> PIDOutputCallback;

class PIDSourceAdapter: public frc::PIDSource {
public:
	PIDSourceAdapter(PIDSourceProvider p) :
			provider { p } {
	}
	virtual ~PIDSourceAdapter() {
	}
	virtual double PIDGet() override {
		return provider();
	}
private:
	PIDSourceProvider provider;
};

class PIDOutputAdapter: public frc::PIDOutput {
public:
	PIDOutputAdapter(PIDOutputCallback cb) :
			callback { cb } {
	}
	virtual ~PIDOutputAdapter() {
	}

	virtual void PIDWrite(double value) override {
		callback(value);
	}

private:
	PIDOutputCallback callback;
};

//class PIDAdapter: public frc::PIDController {
//public:
//	PIDAdapter(double p, double i, double d, double f,
//			PIDSourceProvider provider, PIDOutputCallback cb,
//			double period = 0.05) : frc::PIDController(p,i,d,f,this,this,period){ }
//
//private:
//	PIDOutputAdapter *dst;
//	PIDSourceAdapter *src;
//
//};

} /* namespace utils */

#endif /* SRC_PIDSTUFF_H_ */
