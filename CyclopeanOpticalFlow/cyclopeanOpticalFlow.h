#pragma once
#include <iostream>
#include <vector>

//-----------------------------------------------------Main Functions----------------------------------------------------------

std::vector<double> pyr_flow_1d_v0(int iterations, const std::vector<std::vector<double>>& list_v0, double p0, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f1, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f2, int e_threshold = 0, double threshold = 0.01);

std::vector<double> testPyramidalFlow(const std::vector<std::vector<double>>& list_v0, double p0, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f1, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f2, int e_threshold = 0, double threshold = 0.01, int iterations = 10);

std::vector<std::vector<double>> cyclopeanOpticalFlowRow(int iterations, const std::vector<std::vector<double>>& list_v0, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f1, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f2, double start, double end, int e_threshold = 0, double threshold = 0.01);

std::vector<double> cyclopeanOpticalFlowPoint(int iterations, const std::vector<std::vector<double>>& list_v0, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f1, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f2, double p0, int e_threshold = 0, double threshold = 0.01);