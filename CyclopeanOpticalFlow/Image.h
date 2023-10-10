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

		// Matrix to store the image data.
		Matrix2D<T> imData;
		// Number of rows in the image.
		int rows;
		// Number of columns in the image.
		int columns;

	public:
		// Default constructor initializes rows and columns to zero.
		Image() : rows(0), columns(0) {}

		// Constructor that initializes the Image object from an OpenCV Mat.
		Image(const cv::Mat& im);

		// Constructor that initializes the Image object from a Matrix2D.
		Image(const Matrix2D<T>& imData) : imData(imData), rows(imData.size()), columns(imData[0].size()) {}

		//TODO: Make it so we can analize in between the continuous function
		// Generates a pyramid of functions based on a specific row and up to a specified level.
		std::vector<fun<T>> generatePyramidFunctions(int row, int maxLevel) const;

		// Generates a matrix where each row is a pyramid of functions up to a specified level.
		Matrix2D<fun<T>> generatePyramidFunctionMatrix(int maxLevel) const;

	};


	//TODO: Make it possible to slice data
	// Constructor implementation for OpenCV Mat input.
	template <class T>
	Image<T>::Image(const cv::Mat& im) {
		// Resize the internal matrix to match the input image dimensions.
		imData.resize(im.rows, std::vector<T>(im.cols));

		// Iterate over the rows and columns of the input image and extract intensity values.
		for (size_t row = 0; row < im.rows; row++) {
			for (size_t col = 0; col < im.cols; col++) {
				// Convert the pixel value to type T and store it in imData.
				T intensity = static_cast<T>im.at<uchar>(row, col);
				imData[row][col] = intensity;
			}
		}

		// Update the rows and columns attributes.
		rows = imData.size();
		columns = imData[0].size();
	};

	// Method to generate a pyramid of functions for a specific row.
	template <class T>
	inline std::vector<fun<T>> Image<T>::generatePyramidFunctions(int row, int maxLevel) const{
		//TODO: Assert that row is within the limit

		// Method to generate a pyramid of functions for a specific row.
		return generatePyramidFunctionLevels(imData[row], maxLevel);
	}

	
	// Method to generate a matrix of pyramid functions.
	template <class T>
	Matrix2D<fun<T>> Image<T>::generatePyramidFunctionMatrix(int maxLevel) const{
		Matrix2D<fun<T>> solution;

		for (size_t row = 0; row < rows; row++) {
			// For each row in the image, generate pyramid functions and append them to 'solution'.
			solution.push_back(this->generatePyramidFunctions(row, maxLevel));
		}

		return solution;
	}
}