#pragma once
#include <vector>
#include <boost/math/interpolators/cardinal_cubic_b_spline.hpp>

//TODO: Maybe move definition of fun to a more general file related to functions
//TODO: This all can be more optimized

// Define a template alias for the boost's cardinal cubic b spline interpolator.
template<typename T>
using fun = boost::math::interpolators::cardinal_cubic_b_spline<T>;

// Generates a sequence of spline functions, each representing a level of a pyramid structure.
template<typename T>
std::vector<fun<T>> generatePyramidFunctionLevels(const std::vector<T>& data, int maxLevel) {
    std::vector<fun<T>> listFunctions; // Stores the functions for each pyramid level.
    fun<T> nextLevelFunction;          // Placeholder for function at the current pyramid level.
    std::vector<T> nextLevelData;      // Data for the current pyramid level.
    std::vector<T> nextLevelCoord;

    nextLevelData = data;

    // Iterate over pyramid levels.
    for (int i = 0; i <= maxLevel; i++) {
        // Generate a spline function for the current pyramid level.
        nextLevelFunction = generateFunction(nextLevelData, (int)nextLevelData.size(), (T)0.0, (T)1.0);
        listFunctions.push_back(nextLevelFunction);

        // Compute data for the next pyramid level.
        nextLevelData = nextPyramidalLevel(nextLevelData);
    }

    return listFunctions;
}

//TODO: Make it so we can slice the data
// Generate a cardinal cubic b spline function given a data line.
// Size indicates the number of data points, start and step provide spacing information.
template<typename T>
fun<T> generateFunction(const std::vector<T>& line, int size, T start, T step) {

    fun<T> spline(line.data(), size, start, step);

    return spline;
}

// Compute the data for the next pyramid level.
template<typename T>
std::vector<T> nextPyramidalLevel(std::vector<T>& line) {

    std::vector<T> line_pad(line);

    // Add padding to the data.
    padVector(line_pad, 2, 2);

    // Apply Gaussian convolution to the padded data.
    std::vector<T> kernel;
    kernel = gaussianKernel((T)0.3);

    std::vector<T> line_convolution;
    line_convolution.reserve(line_pad.size());
    convolution(kernel, line_pad, line_convolution);

    // Compute the mean of adjacent data points.
    std::vector<T> line_mean_partition;
    line_mean_partition.reserve(line_mean_partition.size() + 1);
    meanPartition(line_convolution, line_mean_partition);

    //TODO: No subsampling of 2
    return line_convolution;  // Currently returning convoluted data without subsampling.
}

//Todo: Check types here
// Convolve the list with the given kernel and store the result in the output.
template<typename T>
void convolution(const std::vector<T>& kernel, const std::vector<T>& list, std::vector<T>& output) {
    int size = (int)list.size() - (int)kernel.size() + 1;
    output.resize(size);

    // Convolution computation.
    for (int i = 0; i < size; i++) {
        output[i] = 0;
        for (int j = 0; j < (int)kernel.size(); j++) {
            output[i] += kernel[j] * list[i + j];
        }
    }
}

// Add padding to the beginning and end of the vector.
template<typename T>
void padVector(std::vector<T>& vec, int pad_begin, int pad_end) {
    vec.insert(vec.begin(), pad_begin, 0.0); // Pad beginning with zeroes.
    vec.insert(vec.end(), pad_end, 0.0); // Pad end with zeroes
}

// Generate a Gaussian kernel with given parameter a.
template<typename T>
std::vector<T> gaussianKernel(T a) {
    std::vector<T> result = { 1 - a * 2, 1, a * 4, 1, 1 - a * 2 };
    T k = (T)0.25; // 1/4
    std::for_each(result.begin(), result.end(), [k](T& c) { c *= k; }); // Scale each value by k.

    return result;
}

// Computes the mean value of adjacent data points and stores them in the solution_line.
template<typename T>
void meanPartition(const std::vector<T>& line, std::vector<T>& solution_line) {

    //TODO: fix for odd size, it´s still missing to take into count the last number with line.size()-1
    // TODO: handle odd-sized lines.
    for (auto i = 0; i < line.size() - 1; i += 2) {
        solution_line.push_back((line[i] + line[i + 1]) * (T)0.5);

    }
}

