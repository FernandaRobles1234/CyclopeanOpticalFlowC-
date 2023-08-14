#pragma once
#include <iostream>
#include <vector>
#include "tools.h"


template<class T>
Matrix2D<T> new_values(const Matrix2D<T>& list_v0, int size, const std::vector<T>& v0, int e_threshold, bool testingMode= false) {

	// Create a random number generator
	 // Create a random number generator
	std::mt19937 gen;
	if (testingMode == true) {
		gen = std::mt19937(FIXED_SEED);
	}
	else {
		std::random_device rd;
		gen = std::mt19937(rd());
	}

	std::vector<T> new_v0;
	Matrix2D<T> list_new_v0;
	list_new_v0.reserve(size);

	T v1 = v0[0];
	T v2 = v0[1];
	T e = v0[2];
	T f = v0[3];

	T v = v1 + v2;

	// Create a uniform real distribution object
	std::uniform_real_distribution<T> dist(0, v);

	//When threshold is met, no further iteration is done
	if (e > e_threshold) {
		new_v0 = { 0, 0 };
		list_new_v0.push_back(new_v0);
		return list_new_v0;
	}

	//TODO: Maybe allow the tolerance is not as hight?
	if (v != 0) {
		T x;
		T y;
		T distance;

		for (int i = 0; i < size; i++) {

			do {
				// Generate a random number between 0 and v
				x = dist(gen);
				y = dist(gen);

				distance = (x + y);

			} while (!isEqualL(v, distance));

			list_new_v0.push_back({ x,y });
		}

		return list_new_v0;
	}
	else {
		return list_v0;
	}
}

//TODO: Fake converge case
//TODO: pick the value with less e?
template<class T, class Condition>
std::vector<T> pickNewValues(const Matrix2D<T>& listV0, int e_threshold, Condition condition) {
	Matrix2D<T> converged_values;
	converged_values.reserve(listV0.size());
	Matrix2D<T> ok_values;
	ok_values.reserve(listV0.size());
	Matrix2D<T> random_values;
	random_values.reserve(listV0.size());

	for (std::vector<T> v0 : listV0) {

		T v1 = v0[0];
		T v2 = v0[1];
		T e = v0[2];
		T f = v0[3];

		if ((T)f == 5 && e <= e_threshold && condition(v1, v2)) {
			converged_values.push_back(v0);
		}
		else if (e <= e_threshold && condition(v1, v2)) {
			ok_values.push_back(v0);
		}
		else {
			random_values.push_back(v0);
		}
	}

	
	if (!converged_values.empty()) {
		return converged_values[0];
	}
	else if (!ok_values.empty()) {
		return ok_values[0];
	}
	else {
		return { 0, 0, random_values[0][2], random_values[0][3] };
	}
}





std::vector<double> upgrade_1d(const std::vector<double>& v0, double p0, boost::math::interpolators::cardinal_cubic_b_spline<double> f1, boost::math::interpolators::cardinal_cubic_b_spline<double> f2, int e_threshold, double threshold);

std::vector<double> pyr_flow_1d_v0(int iterations, const std::vector<std::vector<double>>& list_v0, double p0, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f1, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f2, int e_threshold = 0, double threshold = 0.01);

std::vector<double> testPyramidalFlowPoint(const std::vector<std::vector<double>>& list_v0, double p0, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f1, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f2, int e_threshold = 0, double threshold = 0.01, int iterations = 10);

std::vector<std::vector<double>> cyclopeanOpticalFlowRow(int iterations, const std::vector<std::vector<double>>& list_v0, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f1, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f2, double start, double end, int e_threshold = 0, double threshold = 0.01);

std::vector<double> cyclopeanOpticalFlowPoint(int iterations, const std::vector<std::vector<double>>& list_v0, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f1, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f2, double p0, int e_threshold = 0, double threshold = 0.01);