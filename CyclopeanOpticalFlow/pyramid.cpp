#include <iostream>
#include <vector>
#include <algorithm>
#include "pyramid.h"
#include <boost/math/interpolators/cardinal_cubic_b_spline.hpp>
#include "imageTools.h"
#include <cmath>


void convolution(const std::vector<double>& kernel, const std::vector<double>& list, std::vector<double>& output) {
    int size = list.size() - kernel.size() + 1;
    output.resize(size);

    for (int i = 0; i < size; i++) {
        output[i] = 0;
        for (int j = 0; j < kernel.size(); j++) {
            output[i] += kernel[j] * list[i + j];
        }
    }
}

void pad_vector(std::vector<double>& vec, int pad_begin, int pad_end) {
    vec.insert(vec.begin(), pad_begin, 0.0); // Pad beginning
    vec.insert(vec.end(), pad_end, 0.0); // Pad end
}

std::vector<double> gaussian_kernel(double a) {
	std::vector<double> result = { 1 - a * 2, 1, a * 4, 1, 1 - a * 2 };
	double k = 0.25; // 1/4
	std::for_each(result.begin(), result.end(), [k](double& c) { c *= k; });

	return result;
}

void mean_partition(const std::vector<double> &line, std::vector<double>& solution_line) {

    //TODO: fix for odd size, it´s still missing to take into count the last number with line.size()-1
    for (auto i = 0; i < line.size()-1; i += 2) {
        solution_line.push_back((line[i] + line[i + 1]) * 0.5);

    }
}

std::vector<double> nextPyramidalLevel(std::vector<double> &line) {
   
    std::vector<double> line_pad(line);
    pad_vector(line_pad, 2, 2);

    std::vector<double> kernel;
    kernel = gaussian_kernel(0.3);

    std::vector<double> line_convolution;
    line_convolution.reserve(line_pad.size());
    convolution(kernel,line_pad,line_convolution);

    std::vector<double> line_mean_partition;
    line_mean_partition.reserve(line_mean_partition.size() + 1);
    mean_partition(line_convolution, line_mean_partition);

    return line_mean_partition;
}

//TODO: Make it so we can slice the data
boost::math::interpolators::cardinal_cubic_b_spline<double> generateFunction(const std::vector<double>& line, int size, double start, double step) {

    boost::math::interpolators::cardinal_cubic_b_spline<double> spline(line.data(), size, start, step);

    return spline;
}

std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> generatePyramidFunctions(const std::vector<double>& data, int maxLevel) {
    std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> listFunctions;
    boost::math::interpolators::cardinal_cubic_b_spline<double> nextLevelFunction;
    std::vector<double> nextLevelData;

    nextLevelData = data;

    for (int i = 0; i < maxLevel+1; i++) {
        nextLevelFunction = generateFunction(nextLevelData, nextLevelData.size(), 0, std::pow(2, i));
        listFunctions.push_back(nextLevelFunction);

        nextLevelData = nextPyramidalLevel(nextLevelData);
    }

    return listFunctions;
}

