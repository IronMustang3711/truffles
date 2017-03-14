/*
 * VerticalLinePipeline.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: jason
 */

#include <vision/VerticalLinePipeline.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <math.h>

void VerticalLinePipeline::Process(cv::Mat& mat) {
	cv::Mat rot_mat( 2, 3, CV_32FC1 );
	rot_mat = cv::getRotationMatrix2D(cv::Point2f(0,0),90,1.0);

	cv::Mat work;
	cv::Mat work2;

	cv::Mat src;
	src = mat.clone();



	cv::warpAffine(mat,work,rot_mat,mat.size());
	cv::GaussianBlur(work,work2,cv::Size(5,5),3,3,cv::BORDER_DEFAULT);
	cv::Canny(work2,work,384,350,3,true);

	work.copyTo(mat);

	cv::rectangle(mat,cv::Point(5,5),cv::Point(100,100), cv::Scalar(255,0,0));//TODO: figure out ROI.



}
