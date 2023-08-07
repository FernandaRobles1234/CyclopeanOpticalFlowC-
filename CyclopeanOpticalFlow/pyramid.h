#pragma once
#include <vector>
#include <boost/math/interpolators/cardinal_cubic_b_spline.hpp>

//Debug pyramid

template<typename T>
using Vectorfun = std::vector<boost::math::interpolators::cardinal_cubic_b_spline<T>>;

template<typename T>
using fun = boost::math::interpolators::cardinal_cubic_b_spline<T>;

template<typename T>
Vectorfun<T> generatePyramidFunctions(const std::vector<T>& data, int maxLevel) {
    Vectorfun<T> listFunctions;
    fun<T> nextLevelFunction;
    std::vector<T> nextLevelData;

    nextLevelData = data;

    for (int i = 0; i < maxLevel + 1; i++) {
        nextLevelFunction = generateFunction(nextLevelData, nextLevelData.size(), 0, std::pow(2, i));
        listFunctions.push_back(nextLevelFunction);

        nextLevelData = nextPyramidalLevel(nextLevelData);
    }

    return listFunctions;
}

//TODO: Make it so we can slice the data
template<typename T>
fun<T> generateFunction(const std::vector<T>& line, int size, T start, T step) {

    fun<T> spline(line.data(), size, start, step);

    return spline;
}

//Todo: Check types here
template<typename T>
void convolution(const std::vector<T>& kernel, const std::vector<T>& list, std::vector<T>& output) {
    int size = list.size() - kernel.size() + 1;
    output.resize(size);

    for (int i = 0; i < size; i++) {
        output[i] = 0;
        for (int j = 0; j < kernel.size(); j++) {
            output[i] += kernel[j] * list[i + j];
        }
    }
}

template<typename T>
void padVector(std::vector<T>& vec, int pad_begin, int pad_end) {
    vec.insert(vec.begin(), pad_begin, 0.0); // Pad beginning
    vec.insert(vec.end(), pad_end, 0.0); // Pad end
}

template<typename T>
std::vector<T> gaussianKernel(T a) {
    std::vector<T> result = { 1 - a * 2, 1, a * 4, 1, 1 - a * 2 };
    T k = 0.25; // 1/4
    std::for_each(result.begin(), result.end(), [k](T& c) { c *= k; });

    return result;
}

template<typename T>
void meanPartition(const std::vector<T>& line, std::vector<T>& solution_line) {

    //TODO: fix for odd size, it´s still missing to take into count the last number with line.size()-1
    for (auto i = 0; i < line.size() - 1; i += 2) {
        solution_line.push_back((line[i] + line[i + 1]) * 0.5);

    }
}

template<typename T>
std::vector<T> nextPyramidalLevel(std::vector<T>& line) {

    std::vector<T> line_pad(line);
    padVector(line_pad, 2, 2);

    std::vector<T> kernel;
    kernel = gaussianKernel(0.3);

    std::vector<T> line_convolution;
    line_convolution.reserve(line_pad.size());
    convolution(kernel, line_pad, line_convolution);

    std::vector<T> line_mean_partition;
    line_mean_partition.reserve(line_mean_partition.size() + 1);
    meanPartition(line_convolution, line_mean_partition);

    return line_mean_partition;
}