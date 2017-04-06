/*
 * VisionV3.h
 *
 *  Created on: Apr 6, 2017
 *      Author: jason
 */

#ifndef SRC_VISION_VISIONV3_H_
#define SRC_VISION_VISIONV3_H_
#include <vision/VisionPipeline.h>
#include <PIDSource.h>
#include <atomic>
class VisionV3: public frc::VisionPipeline, frc::PIDSource {
public:
	VisionV3();
	virtual void Process(cv::Mat& mat) override;
	virtual double PIDGet() override;
private:
	std::atomic_int pidVal;

};


#endif /* SRC_VISION_VISIONV3_H_ */
