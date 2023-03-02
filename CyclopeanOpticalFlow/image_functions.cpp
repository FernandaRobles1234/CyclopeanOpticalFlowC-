#include "image_functions.h"
#include <vector>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <boost/math/interpolators/cardinal_cubic_b_spline.hpp>


cv::Mat resize_image(const cv::Mat& im, int scale) {
	int im_rows = im.rows;
	int im_cols = im.cols;

	int new_im_rows = im_rows / scale;
	int new_im_cols = im_cols / scale;

	cv::Mat resize_im;

	cv::resize(im, resize_im, cv::Size(new_im_cols, new_im_rows), cv::INTER_LINEAR);

	return resize_im;
	//return im;
}

void display_two_images(const cv::Mat& im1, const cv::Mat& im2) {
	// Displaying two images
	cv::Mat ims;
	cv::hconcat(im1, im2, ims);
	cv::imshow("Display_two_images", ims);

	cv::waitKey(0);
}

std::vector<std::vector<double>> image_data(const cv::Mat& im) {

	std::vector< std::vector<double>> image_pixels(im.rows, std::vector<double> (im.cols,0));

	// Access each pixel and print its value
	for (int row = 0; row < im.rows; row++) {
		for (int col = 0; col < im.cols; col++) {
			int intensity = (double)im.at<uchar>(row, col);
			image_pixels[row][col] = intensity;
		}
	}

	return image_pixels;
}

void print_vector(const std::vector<double>& vector) {

		for (const auto col : vector) {
			std::cout << col << " ";
		}
		std::cout << std::endl;
}

void print_matrix(const std::vector<std::vector<double>>& vector) {

	for (const auto row : vector) {
		for (const auto col : row) {
			std::cout << col << " ";
		}
		std::cout << std::endl;
	}
}

boost::math::interpolators::cardinal_cubic_b_spline<double> function_generation(const std::vector<double> &line, int size, double start, double step) {

	boost::math::interpolators::cardinal_cubic_b_spline<double> spline(line.data(), size, start, step);

	return spline;
}

