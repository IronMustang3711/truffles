/*
 * NewVerticalLinePipeline.cpp
 *
 *  Created on: Mar 17, 2017
 *      Author: jason
 */

#include "NewVerticalLinePipeline.h"

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

#include "../Robot.h"

void NewVerticalLinePipeline::Process(cv::Mat& mat) {
	int width = 320;
	int height = 240;
	int histogram[width];
	char sourceImage[height][width][4]; // TODO: Source image from camera should go in here!
	char buffer[height][width][3];  // Our buffer doesn't need alpha channel

	cv::Mat work;
	cv::Mat work2;

	cv::cvtColor(mat, work, cv::COLOR_BGR2GRAY); //convert our image to grayscale

	//rotate
	cv::warpAffine(work, work2,
			cv::getRotationMatrix2D(cv::Point2f(0, 0), 90+2, 1.0), work.size());

	// Copy image into our array
//	char *arrayP;
//	arrayP = (char*) imaqImageToArray(cameraFrame, IMAQ_NO_RECT, NULL, NULL);
//	memcpy(sourceImage, arrayP, sizeof(sourceImage));


	// Edge detection enhanced for vertical lines
	float matrix[3][3] = { { -1, -1, -1 }, { -1, 9, -1 }, { -1, -1, -1 } };

	for (int x = 1; x < width - 1; x++) {
		for (int y = 1; y < height - 1; y++) {
			int sum = 0;
			for (int my = -1; my <= 1; my++) {
				for (int mx = -1; mx <= 1; mx++) {
					int pos = (y + my) * width + (x + mx);
					float val = sourceImage[y][x][0] + sourceImage[y][x][1]
							+ sourceImage[y][x][2];
					if (val > 180 * 3) {
						sum += matrix[my + 1][mx + 1] * val;
					}
				}
			}
			buffer[y][x][0] = sum / 3.0;
			buffer[y][x][1] = sum / 3.0;
			buffer[y][x][2] = sum / 3.0;
		}
	}

	// Clear our histogram
	memset(histogram, 0, sizeof(histogram));

	// Generate histogram
	int maxHistVal = 0;
	for (int y = height / 2 - 30 - 20; y < height / 2 + 10 + 20; y++) {
		for (int x = 0; x < width; x++) {
			int r = buffer[y][x][0];
			int g = buffer[y][x][1];
			int b = buffer[y][x][2];

			int sum = r + g + b;
			if (sum > 10 * 3) {
				histogram[x] += sum;
			}
		}
	}

	// Figure out what the max histogram value was
	 maxHistVal = 0;
	for (int x = 0; x < width; x++) {
		if (histogram[x] > maxHistVal) {
			maxHistVal = histogram[x];
		}
	}

	// Find right and left side
	int leftPos = -1;
	for (int x = 0; x < width; x++) {
		if ((float) histogram[x] / maxHistVal * 20 > 15 && leftPos == -1) {
			leftPos = x;
		}
	}
	int rightPos = -1;
	for (int x = width - 1; x > 0; x--) {
		if ((float) histogram[x] / maxHistVal * 20 > 15 && rightPos == -1) {
			rightPos = x;
		}
	}

//	Robot::chassis->pegSliderLeft = leftPos;
//	Robot::chassis->pegSliderRight = rightPos;

}
