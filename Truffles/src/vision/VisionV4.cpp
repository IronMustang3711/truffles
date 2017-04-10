/*
 * VisionV4.cpp
 *
 *  Created on: Apr 6, 2017
 *      Author: jason
 */

#include "VisionV4.h"
#include <getopt.h>
#include <iostream>

// library includes
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/videoio.hpp>
#include <opencv2/videoio/videoio_c.h>
#include <cmath>


VisionV4::VisionV4() : pidVal{0} { }

void VisionV4::Process(cv::Mat& src) {
	   // cv::Mat src = cv::imread("img2700.jpg");
	    int start =  0.6*src.cols;
	   // printf("start: %d",start);
	   // cv::Rect roiRect(start,0,src.cols - start,src.rows);
	    cv::Mat roi = cv::Mat(src, cv::Range::all(), cv::Range(start,src.cols));
	  //  printf("roi channels: %d\n",roi.channels());
	    cv::Mat bw;
	    int thresh = 120;
	    cv::inRange(roi, cv::Scalar(thresh,thresh,thresh), cv::Scalar(255,255,255), bw);


	    int len =  0.1*(double)(roi.cols);
	   // printf("len: %d",len);
	    //cv::imshow("IR", bw);

	    cv::Mat erodeMask =  cv::getStructuringElement(cv::MORPH_RECT, cv::Size(len,1));
	    cv::Mat hErodeMask = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7,7));
	    //v::transpose(erodeMask, hErodeMask);
	    cv::Mat eroded, erodedHoriz,erodedHoriz2;

	    cv::morphologyEx(bw, eroded, cv::MorphTypes::MORPH_OPEN, erodeMask,cv::Point(0,0),1,cv::BorderTypes::BORDER_REPLICATE);
	    //cv::erode(bw, eroded, erodeMask);
	    cv::erode(bw,erodedHoriz,hErodeMask);
	    cv::dilate(erodedHoriz, erodedHoriz2, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9,9)),cv::Point(-1,-1),1);

	    cv::subtract(eroded, erodedHoriz2, eroded);
	   // cv::imshow("IR", erodedHoriz2);
	   // cv::imshow("IR", eroded);
	    cv::Mat dark, darkLong;
	    cv::inRange(roi, cv::Scalar::zeros(), cv::Scalar(60,60,60), dark);
	    cv::morphologyEx(dark, darkLong, cv::MorphTypes::MORPH_OPEN, erodeMask,cv::Point(0,0),1,cv::BorderTypes::BORDER_REPLICATE);
	    cv::dilate(darkLong,darkLong,cv::getStructuringElement(cv::MORPH_RECT,cv::Point(12,12)),cv::Point(-1,-1),2);
	    //cv::imshow("IR", darkLong);

	    cv::Mat ld;
	    cv::bitwise_and(eroded, darkLong, ld);
	    cv::dilate(ld, ld, erodeMask);

	    cv::Mat sums;

	    cv::reduce(ld, sums, 1, cv::ReduceTypes::REDUCE_AVG,CV_32S);





	    cv::Mat smoothed;
	    cv::blur(sums, smoothed, cv::Size(1,3));

	    cv::Size size = smoothed.size();
	    cv::Mat normalized(size,CV_8U);

	    cv::normalize(smoothed, normalized, 0,255.0, cv::NormTypes::NORM_MINMAX,CV_8U);

	    cv::Mat normThresh(size,CV_8U);




	    cv::threshold(normalized, normThresh, 200, 255, cv::ThresholdTypes::THRESH_BINARY);
	    cv::Mat dilated;

	    cv::Mat something(sums.size(),CV_64F);
	    normThresh.convertTo(something, CV_64F);
	    cv::Mat plotImg;
	    //cv::plot::createPlot2d(something)->render(plotImg);
	   // cv::imshow("IR", plotImg);

	    cv::dilate(normThresh, dilated, cv::getStructuringElement(cv::MorphShapes::MORPH_RECT, cv::Size(1,3)));

	    cv::Mat localMax;
	    cv::compare(normalized, dilated, localMax, cv::CmpTypes::CMP_EQ);
	    cv::Mat localMax2;
	    cv::bitwise_and(localMax, normThresh, localMax2);


	    std::vector<cv::Point> maxima;

	    cv::findNonZero(localMax2, maxima);

	    std::cout << "maxima: "<<maxima<<std::endl;




	    int sum=0;

	    for (cv::Point max : maxima ) {
	      cv::line(src, cv::Point(0       , max.y),
	                    cv::Point(src.cols, max.y),
	                    cv::Scalar(0,0,255),2);
	        sum+=max.y;
	    }
	    if(!maxima.empty()){
	        sum /= maxima.size();
	         cv::line(src, cv::Point(0 , sum), cv::Point(src.cols, sum), cv::Scalar(255,100,100));
	         //TODO: set pidVal!
	    }

	    cv::rectangle(src, cv::Point(start,5), cv::Point(src.cols-5,src.rows-5), cv::Scalar(0,255,0));


}

double VisionV4::PIDGet() {
	return pidVal.load();
}
