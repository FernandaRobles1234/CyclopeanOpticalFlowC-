#pragma once

#include <vector>
#include <iostream>
#include <boost/math/interpolators/cardinal_cubic_b_spline.hpp>


//-----------------------------------------------------Display Functions, Optical Flow----------------------------------------------------------

int displayFlowLine(std::vector<std::vector<float>>& v, boost::math::interpolators::cardinal_cubic_b_spline<float> f1, boost::math::interpolators::cardinal_cubic_b_spline<float> f2, int start, int end);

int displayFlowPoint(float p0, std::vector<float>& v, boost::math::interpolators::cardinal_cubic_b_spline<float> f1, boost::math::interpolators::cardinal_cubic_b_spline<float> f2, int start, int end);

void display_function(boost::math::interpolators::cardinal_cubic_b_spline<float> f1, boost::math::interpolators::cardinal_cubic_b_spline<float> f2, float start, float end, float step = 1);

int display_vector(std::vector<double> f1, double f1_start, double f1_end, double f1_step, std::vector<double> f2, double f2_start, double f2_end, double f2_step);