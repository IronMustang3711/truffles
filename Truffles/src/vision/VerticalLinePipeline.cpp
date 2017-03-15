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

double length(const cv::Vec4i& v) {
	double x1 = v[0];
	double y1 = v[1];
	double x2 = v[2];
	double y2 = v[3];
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
double computeAngle(const cv::Vec4i& v) {
	double x1 = v[0];
	double y1 = v[1];
	double x2 = v[2];
	double y2 = v[3];
	return (180 * atan2(y2 - y1, x2 - x1) / CV_PI);
}

void VerticalLinePipeline::Process(cv::Mat& mat) {
	cv::Mat rot_mat(2, 3, CV_32FC1);
	rot_mat = cv::getRotationMatrix2D(cv::Point2f(0, 0), 90, 1.0);

	cv::Mat work;
	cv::Mat work2;

//	cv::Mat src;
//	src = mat.clone();

	cv::cvtColor(mat, work, cv::COLOR_BGR2GRAY);

	//cv::warpAffine(work, work2, rot_mat, work.size());
	cv::GaussianBlur(work, work2, cv::Size(5, 5), 3, 3, cv::BORDER_DEFAULT);
	cv::Canny(work2, work, 200, 150, 3, true);

	//work2.copyTo(mat);
	cv::rectangle(mat, cv::Point(130, 20),
			cv::Point(mat.cols - 50, mat.rows - 20), cv::Scalar(255, 0, 0)); //TODO: figure out ROI.

	auto lsd = cv::createLineSegmentDetector(cv::LSD_REFINE_STD);
	std::vector<cv::Vec4i> lines;
	lsd->detect(work, lines);
	//lsd->drawSegments(mat,lines);
	//std::cout << "line count: "<< lines.size() << std::endl;
	double minLen = 30;
	double minAngle = -10; //NOTE: these  angles are for vertically rotated images
	double maxAngle = 10;
	for (auto line : lines) {
//		cv::Point p1(line[0],line[1]);
//					cv::Point p2(line[2],line[3]);
//					cv::line(mat,p1,p2,cv::Scalar(0,200,0),2);
		double len = length(line);
		double angle = computeAngle(line);
		if (len > minLen
				&& ((angle >= minAngle && angle <= maxAngle)
						|| (angle + 180 >= minAngle && angle + 180 <= maxAngle))) {
			cv::Point p1(line[0], line[1]);
			cv::Point p2(line[2], line[3]);
			cv::line(mat, p1, p2, cv::Scalar(0, 255, 0));
		}

	}
}
