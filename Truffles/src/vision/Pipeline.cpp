#include "Pipeline.h"
/**
* Initializes a Pipeline.
*/
Pipeline::Pipeline() {
}
/**
* Runs an iteration of the Pipeline and updates outputs.
*
* Sources need to be set before calling this method. 
*
*/
void Pipeline::Process(){
	//Step New_Size0:
	//input
	double newSizeWidth = 5.0;
	double newSizeHeight = 5.0;
	newSize(newSizeWidth, newSizeHeight, this->newSizeOutput);
	//Step CV_GaussianBlur0:
	//input
	Mat cvGaussianblurSrc = source0;
	Size cvGaussianblurKsize = newSizeOutput;
	double cvGaussianblurSigmax = 3.0;
	double cvGaussianblurSigmay = 3.0;
	int cvGaussianblurBordertype = BORDER_DEFAULT;
	cvGaussianblur(cvGaussianblurSrc, cvGaussianblurKsize, cvGaussianblurSigmax, cvGaussianblurSigmay, cvGaussianblurBordertype, this->cvGaussianblurOutput);
	//Step CV_Canny0:
	//input
	Mat cvCannyImage = cvGaussianblurOutput;
	double cvCannyThreshold1 = 384.0;
	double cvCannyThreshold2 = 350.0;
	double cvCannyAperturesize = 3.0;
	bool cvCannyL2gradient = true;
	cvCanny(cvCannyImage, cvCannyThreshold1, cvCannyThreshold2, cvCannyAperturesize, cvCannyL2gradient, this->cvCannyOutput);
	//Step Find_Lines0:
	//input
	Mat findLinesInput = cvCannyOutput;
	findLines(findLinesInput, this->findLinesOutput);
	//Step Filter_Lines0:
	//input
	vector<Line> filterLinesLines = findLinesOutput;
	double filterLinesMinLength = 62.0;
	double filterLinesAngle[] = {216.9064748201439, 286.6553480475382};
	filterLines(filterLinesLines, filterLinesMinLength, filterLinesAngle, this->filterLinesOutput);
}

/**
 * This method is a generated setter for source0.
 * @param source the Mat to set
 */
void Pipeline::setsource0(Mat &source0){
	source0.copyTo(this->source0);
}
/**
 * This method is a generated getter for the output of a New_Size.
 * @return Size output from New_Size.
 */
Size* Pipeline::getnewSizeOutput(){
	return &(this->newSizeOutput);
}
/**
 * This method is a generated getter for the output of a CV_GaussianBlur.
 * @return Mat output from CV_GaussianBlur.
 */
Mat* Pipeline::getcvGaussianblurOutput(){
	return &(this->cvGaussianblurOutput);
}
/**
 * This method is a generated getter for the output of a CV_Canny.
 * @return Mat output from CV_Canny.
 */
Mat* Pipeline::getcvCannyOutput(){
	return &(this->cvCannyOutput);
}
/**
 * This method is a generated getter for the output of a Find_Lines.
 * @return LinesReport output from Find_Lines.
 */
vector<Line>* Pipeline::getfindLinesOutput(){
	return &(this->findLinesOutput);
}
/**
 * This method is a generated getter for the output of a Filter_Lines.
 * @return LinesReport output from Filter_Lines.
 */
vector<Line>* Pipeline::getfilterLinesOutput(){
	return &(this->filterLinesOutput);
}
	/**
	 * Fills a size with given width and height.
	 * @param width the width of the size.
	 * @param height the height of the size.
	 * @param size the size to fill.
	 */
	void Pipeline::newSize(double width, double height, Size &size) {
		size.height = height;
		size.width = width;
	}
	/**
	 * Performs a Gaussian blur on the image.
	 * @param src the image to blur.
	 * @param kSize the kernel size.
	 * @param sigmaX the deviation in X for the Gaussian blur.
	 * @param sigmaY the deviation in Y for the Gaussian blur.
	 * @param borderType pixel extrapolation method.
	 * @param dst the output image.
	 */
	void Pipeline::cvGaussianblur(Mat &src, Size &kSize, double sigmaX, double sigmaY, int borderType, Mat &dst) {
		GaussianBlur(src, dst, kSize, sigmaX, sigmaY, borderType);
	}
	/**
	 * Applies a canny edge detection to the image.
	 * @param image image to use.
	 * @param thres1 first threshold for the canny algorithm.
	 * @param thres2 second threshold for the canny algorithm.
	 * @param apertureSize aperture size for the Sobel operation.
	 * @param gradient if the L2 norm should be used.
	 * @param edges output of the canny.
	 */
	void Pipeline::cvCanny(Mat &image, double thres1, double thres2, double apertureSize, bool gradient, Mat &edges) {
		Canny(image, edges, thres1, thres2, (int)apertureSize, gradient);
	}
	/**
	 * Finds all line segments in an image.
	 *
	 * @param input The image on which to perform the find lines.
	 * @param lineList The output where the lines are stored.
	 */
	void Pipeline::findLines(Mat &input, vector<Line> &lineList) {
		Ptr<LineSegmentDetector> lsd = createLineSegmentDetector(LSD_REFINE_STD);
		vector<Vec4i> lines;
		lineList.clear();
		if (input.channels() == 1) {
			lsd->detect(input, lines);
		} else {
			// The line detector works on a single channel.
			Mat tmp;
			cvtColor(input, tmp, COLOR_BGR2GRAY);
			lsd->detect(tmp, lines);
		}
		// Store the lines in the LinesReport object
		if (!lines.empty()) {
			for (int i = 0; i < lines.size(); i++) {
				Vec4i line = lines[i];
				lineList.push_back(Line(line[0], line[1], line[2], line[3]));
			}
		}
	}
	/**
	 * Filters out lines that do not meet certain criteria.
	 *
	 * @param inputs The lines that will be filtered.
	 * @param minLength The minimum length of a line to be kept.
	 * @param angle The minimum and maximum angle of a line to be kept.
	 * @param outputs The output lines after the filter.
	 */
	void Pipeline::filterLines(vector<Line> &inputs, double minLength, double angle[], vector<Line> &outputs) {
	outputs.clear();
	for (Line line: inputs) {
		if (line.length()>abs(minLength)) {
			if ((line.angle() >= angle[0] && line.angle() <= angle[1]) ||
					(line.angle() + 180.0 >= angle[0] && line.angle() + 180.0 <=angle[1])) {
				outputs.push_back(line);
			}
		}
	}
	}

