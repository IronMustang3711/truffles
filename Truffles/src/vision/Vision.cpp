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
#include "VisionV3.h"
#include "VisionV4.h"
#include <SmartDashboard/SmartDashboard.h>


Vision& Vision::getInstance() {
	static Vision instance;
	return instance;
}

Vision::Vision()  {
	auto v3 = new VisionV3();
	auto v4 = new VisionV4();
	algChooser.AddDefault("Multiscale Template Convolution", v3);
	algChooser.AddObject("morphological op based detector",v4);
	impl = v3;
	frc::SmartDashboard::PutData("vision alg",&algChooser);

}

double Vision::PIDGet() {
	return impl->PIDGet();
}

Vision::~Vision() {
}

void Vision::start() {
	if (active.load()) {
		return;
	}
	impl = algChooser.GetSelected();
	active = true;
	visionThread = std::thread(&Vision::loop, this);
	visionThread.detach(); //TODO do we really want to detach?
	//see http://en.cppreference.com/w/cpp/thread/thread/detach
	//specifically, is thread.join() a valid call after this?
}

void Vision::stop() {
    if(!active.load()){
        return;
    }
	active = false;
	if(visionThread.joinable()) visionThread.join();


}
void Vision::loop() {
	cs::CvSink cvSink = frc::CameraServer::GetInstance()->GetVideo();
	//TODO output is only needed for debugging;
	cs::CvSource outputStream = frc::CameraServer::GetInstance()->PutVideo("vision",
			320, 240);


	cv::Mat src;
	while (active.load()) {

		if (cvSink.GrabFrame(src) == 0) {
			outputStream.NotifyError(cvSink.GetError());
			continue;
		}
		impl->Process(src);
		outputStream.PutFrame(src);
	}
	outputStream.SetConnected(false); //clean up stream(hopefully)
}

