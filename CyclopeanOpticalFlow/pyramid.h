#pragma once
#include <vector>
#include <boost/math/interpolators/cardinal_cubic_b_spline.hpp>

std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> generatePyramidFunctions(const std::vector<double>& line, int max_level= 1);