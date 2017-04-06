/*
 * VisionV3.cpp
 *
 *  Created on: Apr 6, 2017
 *      Author: jason
 */

#include <vision/VisionV3.h>
// system includes
#include <getopt.h>
#include <iostream>

// library includes
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/videoio.hpp>
#include <opencv2/videoio/videoio_c.h>
#include <cmath>
void VisionV3::Process(cv::Mat& src)  {

	  cv::Mat bw{src.size(),CV_8U};
	    cv::cvtColor(src, bw, cv::ColorConversionCodes::COLOR_BGR2GRAY);
	    int start = 0.6*bw.cols;
	    cv::Mat roi(bw, cv::Range::all(), cv::Range(start,src.cols));
	   // cv::Mat blurred;//{bw.size(),CV_8U};
	    //cv::blur(roi, blurred, cv::Size(45,3)); //TODO use integral image?




	    const int nOctaves = 3;

	    cv::Mat G = roi.clone();

	    std::vector<cv::Mat> gp{G};
	    for (int i=0;i<nOctaves;++i) {
	        cv::Mat Gdown;
	        cv::pyrDown(G, G); //TODO look at default params
	        gp.push_back(G.clone());
	    }

	    std::vector<cv::Mat> lp = {gp[gp.size()-1]};

	    //    for(auto it = gp.end(), stop = gp.begin(); it!=stop;--it){
	    //
	    //    }
	    for(int i=nOctaves;i>0;--i){
	        cv::Mat gg;
	        cv::Mat gpDown = gp[i];
	        cv::pyrUp(gpDown, gg);
	        cv::Mat L;
	        cv::Mat gpUp = gp[i-1];
	        cv::subtract(gpUp, gg, L);
	        lp.push_back(L);
	    }

	    cv::Mat kernelMat = (cv::Mat_<int8_t>(15,1) << -1, -1, -1, -2, 0, 1, 0, -3, 0, 1, 0, -2, -1, -1,-1);

	    for (size_t i=0;i<lp.size();i++) {
	        cv::Mat mat = lp[i];
	        cv::Mat filtered{mat.size(),CV_8U};
	        cv::filter2D(mat, filtered, CV_8U, kernelMat);
	        lp[i] = filtered;
	    }

	    cv::Mat reconstructed = *lp.begin();
	    for (size_t i=1; i<=nOctaves; ++i) {
	        cv::pyrUp(reconstructed, reconstructed);
	        cv::add(reconstructed, lp[i], reconstructed);
	    }

	    cv::Mat hist;
	    cv::reduce(reconstructed, hist,/*reduce to single col*/ 1, cv::ReduceTypes::REDUCE_SUM,CV_32S);
	    //double* minVal,
	    //    CV_OUT double* maxVal = 0, CV_OUT Point* minLoc = 0,
	    //    CV_OUT Point* maxLoc = 0
	    double minVal = 0;
	    double maxVal = 0;
	    cv::Point minPoint;
	    cv::Point maxPoint;
	    cv::minMaxLoc(hist, &minVal, &maxVal,&minPoint,&maxPoint);

	    if(maxVal>= 4000){
          int  distanceFromCenter =  std::abs((src.rows / 2) - 40 - maxPoint.y);
          	 pidVal = distanceFromCenter;
	        cv::line(src, cv::Point(0,maxPoint.y), cv::Point(src.cols,maxPoint.y), cv::Scalar(5,5,255),2);
	    } else {
	    	pidVal = 0;
	    }

}

VisionV3::VisionV3(): pidVal{0} {
}

double VisionV3::PIDGet() {
	return pidVal.load();
}
