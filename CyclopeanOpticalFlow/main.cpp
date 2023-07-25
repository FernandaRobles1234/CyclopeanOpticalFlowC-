#include <iostream>
#include <typeinfo>
#include <boost/math/interpolators/cardinal_cubic_b_spline.hpp>
#include <opencv2/core/core.hpp>

#include "imageTools.h"
#include "cyclopeanOpticalFlow.h"
#include "tools.h"
#include "pyramid.h"
#include "displayResults.h"
#include "exportResults.h"

void estimateOpticalFlow(cv::Mat im1, cv::Mat im2);

int main(int argc, char* argv[]) {

	// Processing the images
	int scale = atoi(argv[3]);
	cv::Mat im1 = resizeImage(cv::imread(argv[1], cv::IMREAD_GRAYSCALE), scale);
	cv::Mat im2 = resizeImage(cv::imread(argv[2], cv::IMREAD_GRAYSCALE), scale);

	// Error: Empty image
	if (im1.empty() || im2.empty()) {
		std::cout << "Image File "
			<< "Not Found" << std::endl;

		// wait for any key press
		std::cin.get();
		return -1;
	}

	//Estimate Optical Flow
	estimateOpticalFlow(im1, im2);

	return 0;
}

void estimateOpticalFlow(cv::Mat im1, cv::Mat im2) {
	// Get image data
	std::vector< std::vector<double>> im1_data;
	im1_data = obtainImageData(im1);

	std::vector< std::vector<double>> im2_data;
	im2_data = obtainImageData(im2);

	std::vector<double> row1 = im1_data[10];
	std::vector<double> row2 = im2_data[10];


	//Generate Functions
	int test_n = 0;
	std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> f1_pyr;
	f1_pyr = generatePyramidFunctions(row1, test_n);


	std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> f2_pyr;
	f2_pyr = generatePyramidFunctions(row2, test_n);

	std::vector<std::vector<double>> list_v0;
	//std::vector<std::vector<double>> solution_v;
	std::vector<double> v;

	list_v0 = uniformDistribution2d(10, 0, 2);

	v = cyclopeanOpticalFlowPoint(10, list_v0, f1_pyr, f2_pyr, 10, 0, 0.01);

	std::cout << v[0] << ", " << v[1] << ", " << v[3] << ", " << v[0] + v[1] << std::endl;

	//solution_v = cyclopeanOpticalFlowRow(10, list_v0, f1_pyr, f2_pyr, 0, row1.size(), 0, 0.01);

	//matrixToTxt(solution_v, "row_test.txt");

	//displayFlowLine(solution_v, f1_pyr[0], f2_pyr[0], 0, row1.size());
}