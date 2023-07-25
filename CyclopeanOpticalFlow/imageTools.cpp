#include "imageTools.h"

#include <vector>
#include <opencv2/opencv.hpp>
#include <iostream>


cv::Mat resizeImage(const cv::Mat& im, int scale) {
	int im_rows = im.rows;
	int im_cols = im.cols;

	int new_im_rows = im_rows / scale;
	int new_im_cols = im_cols / scale;

	cv::Mat resize_im;

	cv::resize(im, resize_im, cv::Size(new_im_cols, new_im_rows), cv::INTER_LINEAR);

	return resize_im;
}

std::vector<std::vector<double>> obtainImageData(const cv::Mat& im) {

	std::vector< std::vector<double>> im_pixels(im.rows, std::vector<double>(im.cols, 0));

	// Access each pixel and give it a value
	for (int row = 0; row < im.rows; row++) {
		for (int col = 0; col < im.cols; col++) {
			int intensity = (double)im.at<uchar>(row, col);
			im_pixels[row][col] = intensity;
		}
	}

	return im_pixels;
}

