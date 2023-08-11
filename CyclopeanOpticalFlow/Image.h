#pragma once

#include <opencv2/core/core.hpp>
#include "tools.h"
#include "pyramid.h"

//TODO: Make it possible to slice data, so we can pick wich rows to use as input rather than the whole image
//Full image for the moment
//TODO: Maybe do this Image object as a stereo pair
namespace cof {
	template <class T>
	class Image {
		//TODO: How much should we reserve?
		//TODO: Assert data.len > 5 
		std::vector< std::vector<T>> imData;
		int rows;
		int columns;

	public:
		Image() : rows(0), columns(0) {}

		Image(const cv::Mat& im);

		Image(const std::vector<std::vector<T>>& imData) : imData(imData), rows(imData.size()), columns(imData[0].size()) {}

		//TODO: Make it so we can analize in between the continuous function
		std::vector<fun<T>> generatePyramidFunctions(int row, int maxLevel) const;

		std::vector<std::vector<fun<T>>> generatePyramidFunctionMatrix(int maxLevel) const;

	};


	//TODO: Make it possible to slice data
	template <class T>
	Image<T>::Image(const cv::Mat& im) {

		imData.resize(im.rows, std::vector<T>(im.cols));

		for (size_t row = 0; row < im.rows; row++) {
			for (size_t col = 0; col < im.cols; col++) {
				T intensity = static_cast<T>im.at<uchar>(row, col);
				imData[row][col] = intensity;
			}
		}

		rows = imData.size();
		columns = imData[0].size();
	};

	template <class T>
	inline std::vector<fun<T>> Image<T>::generatePyramidFunctions(int row, int maxLevel) const{
		//TODO: Assert that row is within the limit
		return generatePyramidFunctionLevels(imData[row], maxLevel);
	}

	template <class T>
	std::vector<std::vector<fun<T>>> Image<T>::generatePyramidFunctionMatrix(int maxLevel) const{
		std::vector<std::vector<fun<T>>> solution;

		for (size_t row = 0; row < rows; row++) {
			solution.push_back(this->generatePyramidFunctions(row, maxLevel));
		}

		return solution;
	}

}