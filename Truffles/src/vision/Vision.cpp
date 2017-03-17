/*
 * Vision.cpp
 *
 *  Created on: Mar 15, 2017
 *      Author: jason
 */

#include <CameraServer.h>
#include "Vision.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "vision/VisionRunner.h"
#include "VerticalLinePipeline.h"

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

double Vision::PIDGet() {
	return 0; //TODO!
}

Vision::~Vision() {
}

void Vision::start() {
	if (active.load()) {
		return;
	}
	active = true;
	visionThread = std::thread(&Vision::loop, this);
	visionThread.detach(); //TODO do we really want to detach?
	//see http://en.cppreference.com/w/cpp/thread/thread/detach
	//specifically, is thread.join() a valid call after this?
}

void Vision::stop() {
	active = false;
	if(visionThread.joinable()) visionThread.join();


}
void Vision::loop() {
	cs::CvSink cvSink = frc::CameraServer::GetInstance()->GetVideo();
	//TODO output is only needed for debugging;
	cs::CvSource outputStream = frc::CameraServer::GetInstance()->PutVideo("vision",
			320, 240);

	VerticalLinePipeline pipe;
	cv::Mat src;
	while (active.load()) {

		if (cvSink.GrabFrame(src) == 0) {
			outputStream.NotifyError(cvSink.GetError());
			continue;
		}
		pipe.Process(src);
		outputStream.PutFrame(src);
	}
	outputStream.SetConnected(false); //clean up stream(hopefully)
}

