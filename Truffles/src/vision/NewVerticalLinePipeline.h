/*
 * NewVerticalLinePipeline.h
 *
 *  Created on: Mar 17, 2017
 *      Author: jason
 */

#ifndef SRC_VISION_NEWVERTICALLINEPIPELINE_H_
#define SRC_VISION_NEWVERTICALLINEPIPELINE_H_
#include "vision/VisionPipeline.h"

class NewVerticalLinePipeline : public frc::VisionPipeline {
public:
	virtual void Process(cv::Mat& mat) override;

	int leftPos=0;
	int rightPos=0;
};

#endif /* SRC_VISION_NEWVERTICALLINEPIPELINE_H_ */
