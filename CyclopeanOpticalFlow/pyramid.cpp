#include <iostream>
#include <vector>
#include <algorithm>
#include "pyramid.h"


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
    for (auto i = 0; i < line.size(); i += 2) {
        solution_line.push_back((line[i] + line[i + 1]) * 0.5);
    }
}

std::vector<double> next_pyramidal_level(std::vector<double> &line) {
   
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

