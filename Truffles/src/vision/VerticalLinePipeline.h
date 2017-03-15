/*
 * VerticalLinePipeline.h
 *
 *  Created on: Mar 14, 2017
 *      Author: jason
 */

#ifndef SRC_VISION_VERTICALLINEPIPELINE_H_
#define SRC_VISION_VERTICALLINEPIPELINE_H_
#include "vision/VisionPipeline.h"
class VerticalLinePipeline: public frc::VisionPipeline {
public:
	virtual void Process(cv::Mat& mat) override;
};

#endif /* SRC_VISION_VERTICALLINEPIPELINE_H_ */
