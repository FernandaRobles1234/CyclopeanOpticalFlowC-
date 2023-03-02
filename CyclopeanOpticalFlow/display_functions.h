#pragma once

#include <vector>
#include <iostream>
#include <boost/math/interpolators/cardinal_cubic_b_spline.hpp>




//-----------------------------------------------------Display Functions, Optical Flow----------------------------------------------------------

int line_display_flow(std::vector<std::vector<double>>& v, boost::math::interpolators::cardinal_cubic_b_spline<double> f1, boost::math::interpolators::cardinal_cubic_b_spline<double> f2, int start, int end);

int display_function(boost::math::interpolators::cardinal_cubic_b_spline<double> f1, boost::math::interpolators::cardinal_cubic_b_spline<double> f2, double start, double end, double step= 1);

int display_vector(std::vector<double> f1, double f1_start, double f1_end, double f1_step, std::vector<double> f2, double f2_start, double f2_end, double f2_step);