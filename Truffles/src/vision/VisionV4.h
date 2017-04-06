/*
 * VisionV4.h
 *
 *  Created on: Apr 6, 2017
 *      Author: jason
 */

#ifndef SRC_VISION_VISIONV4_H_
#define SRC_VISION_VISIONV4_H_
#include "VisionPIDPipeline.h"
#include <atomic>
class VisionV4 :  public VisionPIDPipeline {
public:
	VisionV4();
	virtual void Process(cv::Mat& mat) override;
	virtual double PIDGet() override;
private:
	std::atomic_int pidVal;
};

#endif /* SRC_VISION_VISIONV4_H_ */
