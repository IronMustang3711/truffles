/*
 * Vision.cpp
 *
 *  Created on: Mar 15, 2017
 *      Author: jason
 */

#include <vision/Vision.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "commands/auto/Noop.h"
#include "commands/auto/DriveStraight.h"
#include "vision/VisionRunner.h"
#include "vision/VerticalLinePipeline.h"

/*
 * thread stuff:
 * http://stackoverflow.com/questions/16111663/do-i-have-to-use-atomicbool-for-exit-bool-variable
 */

Vision& Vision::getInstance() {
	static Vision instance;
	return instance;
}

Vision::Vision() {
}
Vision::~Vision(){
}

void Vision::start() {
	if(active){ return; }
	active = true;
	visionThread = std::thread(&Vision::loop,this);
	visionThread.detach(); //TODO do we really want to detach?
	//see http://en.cppreference.com/w/cpp/thread/thread/detach
	//specifically, is thread.join() a valid call after this?
}

void Vision::stop() {
	active = false;
	//assert(visionThread.joinable());
	visionThread.join();

}
void Vision::loop(){
	cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();

	cs::CvSource outputStream = CameraServer::GetInstance()->PutVideo("vision",
			320, 240);
	//TODO output is only needed for debugging;

	VerticalLinePipeline pipe;
	cv::Mat src;
	while(active){


		if (cvSink.GrabFrame(src) == 0) {
			outputStream.NotifyError(cvSink.GetError());
			continue;
		}
		pipe.Process(src);
	//	cv::rectangle(src, cv::Point(5, 5), cv::Point(100, 100),
	//			cv::Scalar(255, 0, 0));
		outputStream.PutFrame(src);
	}
	outputStream.SetConnected(false); //clean up stream(hopefully)
}

