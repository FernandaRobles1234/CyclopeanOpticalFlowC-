#pragma once
#include <iostream>
#include <vector>


//-----------------------------------------------------Main Functions----------------------------------------------------------

std::vector<double> upgrade_1d(std::vector<double>& v0, double p0, boost::math::interpolators::cardinal_cubic_b_spline<double> f1, boost::math::interpolators::cardinal_cubic_b_spline<double> f2, int e_threshold=0, double threshold=0.01);

std::vector<std::vector<double>> line_test(int iterations, std::vector<double>& v0, boost::math::interpolators::cardinal_cubic_b_spline<double> f1, boost::math::interpolators::cardinal_cubic_b_spline<double> f2, double start, double end, int e_threshold = 0, double threshold = 0.01);

std::vector<double> flow_1d_v0(int iterations, std::vector<std::vector<double>>& list_v0, double p0, boost::math::interpolators::cardinal_cubic_b_spline<double> f1, boost::math::interpolators::cardinal_cubic_b_spline<double> f2, int e_threshold = 0, double threshold = 0.01);

std::vector<std::vector<double>> line_test_v0(int iterations, std::vector<std::vector<double>>& list_v0, boost::math::interpolators::cardinal_cubic_b_spline<double> f1, boost::math::interpolators::cardinal_cubic_b_spline<double> f2, double start, double end, int e_threshold = 0, double threshold = 0.01);



