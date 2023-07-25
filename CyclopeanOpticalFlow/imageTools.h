#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

// Rezising image
cv::Mat resizeImage(const cv::Mat &im, int scale);

// Obtaining an image's data
std::vector< std::vector<double>> obtainImageData(const cv::Mat& im);


