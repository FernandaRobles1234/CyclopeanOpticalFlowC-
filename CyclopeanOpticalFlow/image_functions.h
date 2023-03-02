#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <boost/math/interpolators/cardinal_cubic_b_spline.hpp>

// Rezising image
cv::Mat resize_image(const cv::Mat &im, int scale);

// Displaying two images
void display_two_images(const cv::Mat &im1,const cv::Mat &im2);

// Obtaining an image's data
std::vector< std::vector<double>> image_data(const cv::Mat &im);

// Visualizes a vector
void print_vector(const std::vector<double>& vector);

// Visualizes a matrix
void print_matrix(const std::vector< std::vector<double>>& vector);

// generates a function f with data line
// Make modifications so we can slice the data
boost::math::interpolators::cardinal_cubic_b_spline<double> function_generation(const std::vector<double>& line, int size, double start = 0, double step = 1);


