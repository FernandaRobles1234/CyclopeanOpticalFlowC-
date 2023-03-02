#pragma once
#include <vector>
#include <boost/math/interpolators/cardinal_cubic_b_spline.hpp>

std::vector<double> next_pyramidal_level(std::vector<double>& line);

std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> pyr_func_gen(std::vector<double> line, int max_level= 1);