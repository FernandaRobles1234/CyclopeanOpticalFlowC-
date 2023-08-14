#pragma once
#include <iostream>
#include <vector>
#include "tools.h"
#include "pyramid.h"


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

template<class T>
std::vector<T> upgrade_1d(const std::vector<T>& v0, T p0, fun<T> f1, fun<T> f2, int e_threshold, T threshold) {

	std::vector<T> v;
	v.reserve(4);

	T v1 = v0[0];
	T v2 = v0[1];
	T e = v0[2];
	T f = v0[3];

	// True if: Error limit is reached (for pyramidal implementation)
	if (e > e_threshold) {
		v = { 0, 0, e, f };
		return v;
	}

	// True if: Error for this pixel instance has been encountered once
	if (f != 0) {
		v = { v1, v2, e, f };
		return v;
	}

	T p1 = p0 - v1;
	T p2 = p0 + v2;

	T c = (f1(p0) + f2(p0)) * 0.5;


	//True if: Gradient sending us to the edge
	if (p1 < 0 || p2 < 0) {
		v = { v1, v2, e + 1, 4 };
		return v;
	}

	T d1 = f1.prime(p1);
	T d2 = f2.prime(p2);

	//TODO: verify this
	T fric_const = 1;
	T fric1 = fric_const * f1.double_prime(p1);
	T fric2 = fric_const * f1.double_prime(p2);


	//True if: Not enought gradient
	if (abs(d1) < threshold || abs(d2) < threshold) {
		v = { v1, v2, e + 1, 1 };
		return v;
	}

	//True if: Different sign encountered 
	if (d1 * d2 < 0) {
		v = { v1, v2, e + 1, 2 };
		return v;
	}

	T c_criteria = 0.3;

	//Create the x vector for peason correlation coefficient
	int c_size = 3;
	T step = 1;
	int inverse_step = 1; // 1/0.2

	assert(step == (1.0 / inverse_step));

	//constructing the vector with this, can give decimal values

	std::vector<T> x_set((c_size + 1) * inverse_step);
	T i(-c_size);
	std::generate(x_set.begin(), x_set.end(), [&i, &step] { return i += step; });

	std::vector<T> p1_set((c_size + 1) * inverse_step);
	std::transform(x_set.begin(), x_set.end(), p1_set.begin(), [&p1](T n) { return p1 + n; });

	std::vector<T> p2_set((c_size + 1) * inverse_step);
	std::transform(x_set.begin(), x_set.end(), p2_set.begin(), [&p2](T n) { return p2 + n; });

	//Create the y vector for peason correlation coefficient
	std::vector<T> y1_set((c_size + 1) * inverse_step);
	std::transform(p1_set.begin(), p1_set.end(), y1_set.begin(), f1);

	std::vector <T> y2_set((c_size + 1) * inverse_step);
	std::transform(p1_set.begin(), p1_set.end(), y2_set.begin(), f2);

	//We calculate the pearson coefficient
	T p_correlation;
	p_correlation = pearsonCorrelation(&y1_set[0], &y2_set[0], (int)y1_set.size());

	//Not good correlation score
	if (p_correlation < c_criteria) {
		v = { v1, v2, e + 1, 3 };
		return v;
	}

	T dv1;
	T dv2;

	bool sign;
	int sign_int;

	sign = ((fric1 > 0) - (fric1 < 0));  // Extracting sign of fric1
	sign_int = (int)sign;

	dv1 = (f1(p1) - c) / (d1 + sign_int * std::abs(fric1));

	sign = ((fric2 > 0) - (fric2 < 0)); // Extracting sign of fric2
	sign_int = (int)sign;
	dv2 = (c - f2(p2)) / (d2 + sign_int * std::abs(fric2));

	std::vector<T> dv = { dv1, dv2 };

	// True if: the norm of the gradient is has found convergence
	T norm = L2Norm(dv);

	if (norm < 0.01) {
		v = { v1 + dv1, v2 + dv2, e, 5 };
		return v;
	}
	else {
		v = { v1 + dv1, v2 + dv2, e, f };
		return v;
	}
}


std::vector<double> upgrade_1d(const std::vector<double>& v0, double p0, boost::math::interpolators::cardinal_cubic_b_spline<double> f1, boost::math::interpolators::cardinal_cubic_b_spline<double> f2, int e_threshold, double threshold);

std::vector<double> pyr_flow_1d_v0(int iterations, const std::vector<std::vector<double>>& list_v0, double p0, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f1, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f2, int e_threshold = 0, double threshold = 0.01);

std::vector<double> testPyramidalFlowPoint(const std::vector<std::vector<double>>& list_v0, double p0, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f1, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f2, int e_threshold = 0, double threshold = 0.01, int iterations = 10);

std::vector<std::vector<double>> cyclopeanOpticalFlowRow(int iterations, const std::vector<std::vector<double>>& list_v0, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f1, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f2, double start, double end, int e_threshold = 0, double threshold = 0.01);

std::vector<double> cyclopeanOpticalFlowPoint(int iterations, const std::vector<std::vector<double>>& list_v0, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f1, std::vector<boost::math::interpolators::cardinal_cubic_b_spline<double>> list_f2, double p0, int e_threshold = 0, double threshold = 0.01);