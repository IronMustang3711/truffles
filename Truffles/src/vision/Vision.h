/*
 * Vision.h
 *
 *  Created on: Mar 15, 2017
 *      Author: jason
 */

#ifndef SRC_VISION_VISION_H_
#define SRC_VISION_VISION_H_
#include <thread>
#include <mutex>
#include <atomic>
#include "VisionPIDPipeline.h"



class Vision : public frc::PIDSource {
public:
	static Vision& getInstance();
	void start();
	void stop();
	virtual double PIDGet() override;

private:
	/**
	 * WARNING: THIS METHOD BLOCKS!
	 */
	void loop();
	Vision();
	~Vision();
	Vision(const Vision&) = delete;
	const Vision& operator=(const Vision) = delete;

	std::thread visionThread;
	std::mutex lock;
	std::atomic_bool active { false };
	VisionPIDPipeline *impl;


};

#endif /* SRC_VISION_VISION_H_ */
