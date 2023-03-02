#include <iostream>
#include <opencv2/core/core.hpp>
#include <typeinfo>
#include <boost/math/interpolators/cardinal_cubic_b_spline.hpp>
#include "image_functions.h"
#include "cyclopean_optical_flow.h"
#include "test_functions.h"
#include "tools.h"
#include "pyramid.h"
#include "display_functions.h"



int main(int argc, char* argv[]) {

	// Processing the images
	int scale = atoi(argv[3]);
	cv::Mat im1 = resize_image(cv::imread(argv[1], cv::IMREAD_GRAYSCALE), scale);
	cv::Mat im2 = resize_image(cv::imread(argv[2], cv::IMREAD_GRAYSCALE), scale);

	// Error Handling
	if (im1.empty() || im2.empty()) {
		std::cout << "Image File "
			<< "Not Found" << std::endl;

		// wait for any key press
		std::cin.get();
		return -1;
	}

	if (false) {
		int type = im1.type();
		std::cout << type << std::endl;
		int num_channels = im1.channels();
		std::cout << num_channels << std::endl;
	}

	// image_data 
	std::vector< std::vector<double>> im1_data;
	im1_data = image_data(im1);

	std::vector< std::vector<double>> im2_data;
	im2_data = image_data(im2);

	//-------------------------------------------Pyramid test---------------------------------------------------------
	std::vector<double> row1_data= im1_data[10];
	std::vector<double> row2_data= im2_data[10];

	for (auto data : row1_data) {
		std::cout << data << " ";
	}
	std::cout << std::endl;
	std::cout << row1_data.size() << std::endl;

	std::vector<double> im1_data_lvl1;
	im1_data_lvl1 = next_pyramidal_level(row1_data);

	std::vector<double> im2_data_lvl1;
	im2_data_lvl1 = next_pyramidal_level(row2_data);

	for (auto col : im1_data_lvl1) {
		std::cout << col << " ";
	}
	std::cout << std::endl;
	std::cout << im1_data_lvl1.size() << std::endl;

	//display_vector(im2_data_lvl1, 0, row2_data.size(), 2, row2_data, 0, row2_data.size(), 1);

	//function_generation
	/*boost::math::interpolators::cardinal_cubic_b_spline<double> f1;
	f1 = function_generation(row1_data, row1_data.size());
	boost::math::interpolators::cardinal_cubic_b_spline<double> f2;
	f2 = function_generation(row2_data, row2_data.size());

	boost::math::interpolators::cardinal_cubic_b_spline<double> f1_lvl1;
	f1_lvl1 = function_generation(im1_data_lvl1, im1_data_lvl1.size(),0, 2);
	boost::math::interpolators::cardinal_cubic_b_spline<double> f2_lvl1;
	f2_lvl1 = function_generation(im2_data_lvl1, im2_data_lvl1.size(), 0, 2);*/

	std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f1;
	list_f1 = pyr_func_gen(row1_data, 3);

	display_function(list_f1[0], list_f1[1], 0, row1_data.size());

	display_function(list_f1[1], list_f1[2], 0, row1_data.size());

	//-------------------------------------------Flow test------------------------------------------------------------

	// function generation with test functions
	//SinFunc f1(0);
	//SinFunc f2(-0.5);

	/*std::vector<std::vector<double>> v_final;
	std::vector<std::vector<double>> list_v0;

	list_v0 = uniform_distribution_2d(10, 0, 1);

	v_final = line_test_v0(10, list_v0, f1_lvl1, f2_lvl1, 0, im1.cols, 0, 0.001);

	line_display_flow(v_final, f1_lvl1, f2_lvl1, 0, im1.cols);*/

	return 0;
}

