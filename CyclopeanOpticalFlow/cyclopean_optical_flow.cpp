#include <iostream>
#include <vector>
#include <cmath>
#include <boost/math/interpolators/cardinal_cubic_b_spline.hpp>
#include "cyclopean_optical_flow.h"
#include "test_functions.h"
#include "tools.h"
#include <cstdlib>
#include <ctime>
#include <random>


//----------------------------------------------------Temporal Functions in this file----------------------------------------------------
double mean(double data[], int n) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += data[i];
	}
	return sum / n;
}

double variance(double data[], int n) {
	double meanValue = mean(data, n);
	double temp = 0;
	for (int i = 0; i < n; i++) {
		temp += (data[i] - meanValue) * (data[i] - meanValue);
	}
	return temp / (n - 1);
}

double covariance(double data1[], double data2[], int n) {
	double mean1 = mean(data1, n);
	double mean2 = mean(data2, n);
	double temp = 0;
	for (int i = 0; i < n; i++) {
		temp += (data1[i] - mean1) * (data2[i] - mean2);
	}
	return temp / (n - 1);
}

double PearsonCorrelation(double data1[], double data2[], int n) {
	return covariance(data1, data2, n) / (sqrt(variance(data1, n)) * sqrt(variance(data2, n)));
}

double L2_norm(const std::vector<double>& v) {
	double sum = 0;
	for (double x : v) {
		sum += x * x;
	}
	return sqrt(sum);
}

std::vector<std::vector<double>> new_values(int size, int e_threshold, std::vector<double> v0, std::vector<std::vector<double>> list_v0) {
	// Create a random number generator
	std::random_device rd;
	std::mt19937 gen(rd());

	std::vector<double> new_v0;
	std::vector<std::vector<double>> list_new_v0;
	list_new_v0.reserve(size);

	double v1 = v0[0];
	double v2 = v0[1];
	double e = v0[2];
	double f = v0[3];

	double v = v1 + v2;

	// Create a uniform real distribution object
	std::uniform_real_distribution<double> dist(0, v);

	if (e > e_threshold) {
		new_v0 = { 0, 0 };
		list_new_v0.push_back(new_v0);
		return list_new_v0;
	}

	if (v != 0 && f == 0) {
		double x, y, distance;

		for (int i = 0; i < size; i++) {

			do {
				// Generate a random number between 0 and v
				x = dist(gen);
				y = dist(gen);

				distance = (x + y);
				//std::cout << (v1 < distance < v2) << " " << distance << " " << i << std::endl;
				//std::cout << 1;

			} while (!(distance == v));

			list_new_v0.push_back({ x,y });
		}
		return list_new_v0;
	}
	else {
		return list_v0;
	}
}

std::vector<double> pick_new_values(std::vector<std::vector<double>> list_v0) {
	

	std::vector<std::vector<double>> converged_values;
	std::vector<std::vector<double>> ok_values;
	std::vector<std::vector<double>> random_values;
	for (auto v0 : list_v0) {

		double v1 = v0[0];
		double v2 = v0[1];
		double e = v0[2];
		double f = v0[3];

		if ((int)f == 5) {
			converged_values.push_back(v0);
		}
		else if((int)f == 0) {
			ok_values.push_back(v0);
		}
		else{
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
		return {0, 0, random_values[0][2], random_values[0][3]};
	}
}

//----------------------------------------------------Main Functions----------------------------------------------------

std::vector<double> upgrade_1d(std::vector<double>& v0, double p0, boost::math::interpolators::cardinal_cubic_b_spline<double> f1, boost::math::interpolators::cardinal_cubic_b_spline<double> f2, int e_threshold, double threshold) {

	std::vector<double> v;
	v.reserve(4);

	double v1 = v0[0];
	double v2 = v0[1];
	double e = v0[2];
	double f = v0[3];

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

	double p1 = p0 - v1;
	double p2 = p0 + v2;

	double c = (f1(p0) + f2(p0)) * 0.5;


	//proposal
	//Gradient sending us to the edge
	if (p1 < 0 || p2 < 0) {
		v = { v1, v2, e + 1, 4};
		return v;
	}

	double d1 = f1.prime(p1);
	double d2 = f2.prime(p2);

	
	double fric_const = 1;
	double fric1 = fric_const * f1.double_prime(p1);
	double fric2 = fric_const * f1.double_prime(p2);

	

	//Not enought gradient
	if (abs(d1) < threshold || abs(d2) < threshold) {
		v = { v1, v2, e+1, 1};
		return v;
	}

	//Different sign encountered 
	if (d1 * d2 < 0) {
		v = { v1, v2, e + 1, 2};
		return v;
	}

	double c_criteria = 0.9;

	//Create the x vector for peason correlation coefficient
	int c_size = 2;
	double step = 0.2;
	int inverse_step = 5; // 1/0.2

	assert(step == (1.0/inverse_step)); 

	//constructing the vector with this, can give decimal values

	std::vector<double> x_set((c_size + 1) * inverse_step);
	double i(-c_size);
	std::generate(x_set.begin(), x_set.end(), [&i, &step] { return i += step; });

	std::vector<double> p1_set((c_size + 1) * inverse_step);
	std::transform(x_set.begin(), x_set.end(), p1_set.begin(), [&p1](double n) { return p1 + n; });

	std::vector<double> p2_set((c_size + 1) * inverse_step);
	std::transform(x_set.begin(), x_set.end(), p2_set.begin(), [&p2](double n) { return p2 + n; });

	//Create the y vector for peason correlation coefficient
	std::vector<double> y1_set((c_size + 1) * inverse_step);
	std::transform(p1_set.begin(), p1_set.end(), y1_set.begin(), f1);

	std::vector <double> y2_set((c_size + 1) * inverse_step);
	std::transform(p1_set.begin(), p1_set.end(), y2_set.begin(), f2);

	//We calculate the pearson coefficient
	double p_correlation;
	p_correlation = PearsonCorrelation(&y1_set[0], &y2_set[0], (int)y1_set.size());

	//Not good correlation score
	if (p_correlation > c_criteria) {
		v = { v1, v2, e + 1, 3};
		return v;
	}

	double dv1;
	double dv2;

	bool sign;
	int sign_int;

	sign = ((fric1 > 0) - (fric1 < 0));  // Extracting sign of fric1
	sign_int = (int)sign;

	dv1 = (f1(p1) - c) / (d1 + sign_int * std::abs(fric1));

	sign = ((fric2 > 0) - (fric2 < 0)); // Extracting sign of fric2
	sign_int = (int)sign;
	dv2 = (c - f2(p2)) / (d2 + sign_int * std::abs(fric2));


	// True if: the norm of the gradient is has found convergence
	double norm = L2_norm({ dv1, dv2 });

	if (norm < 0.01) {
		v = { v1 + dv1, v2 + dv2, e, 5};
		return v;
	}
	else {
		v = { v1 + dv1, v2 + dv2, e, f};
		return v;
	}
}


std::vector<std::vector<double>> line_test(int iterations, std::vector<double>& v0, boost::math::interpolators::cardinal_cubic_b_spline<double> f1, boost::math::interpolators::cardinal_cubic_b_spline<double> f2, double start, double end, int e_threshold, double threshold) {

	std::vector<double> v = v0;
	std::vector<std::vector<double>> list_v;

	for (double x = start; x < end; x++) {
		for (int i = 0; i < iterations; i++) {
			v = upgrade_1d(v, x, f1, f2, e_threshold, threshold);
		}
		list_v.push_back(v);
		v = v0;
	}

	return list_v;
}


std::vector<double> flow_1d_v0(int iterations, std::vector<std::vector<double>>& list_v0, double p0, boost::math::interpolators::cardinal_cubic_b_spline<double> f1, boost::math::interpolators::cardinal_cubic_b_spline<double> f2, int e_threshold, double threshold) {
	int nv_size = (int)list_v0.size();

	std::vector<std::vector<double>> nV;
	nV.reserve(nv_size);

	std::vector<std::vector<double>> list_temporal_values;
	list_temporal_values.reserve(nv_size);

	std::vector<double> update_values{ 0,0,0,0 };

	std::vector<double> temporal_values;
	temporal_values.reserve(update_values.size());


	//This will only give values that sum up to the magnitude of v Or if v0 = 0, list newv0 is created and fed to the function to try all it's contained values
	nV = new_values(nv_size, e_threshold, update_values, list_v0);

	for (auto v : nV) {

		//We initialize whith values calculated at nV and last calculated updateValues [[3;; 4]] *)
		temporal_values = { v[0], v[1], update_values[2], update_values[3] };

		for (int i = 0; i < iterations; i++) {
			temporal_values = upgrade_1d(temporal_values, p0, f1, f2, e_threshold, threshold);
		}
		list_temporal_values.push_back(temporal_values);
	}

	//Implementation of "pick temporal values, We only update updateValues with the tValue that converged
	update_values = pick_new_values(list_temporal_values);

	std::vector<double> solution_v;
	solution_v.reserve(3);

	for (int i = 0; i < 3; i++) {
		solution_v.push_back(update_values[i]);
	}

	return solution_v;
}


std::vector<std::vector<double>> line_test_v0(int iterations, std::vector<std::vector<double>>& list_v0, boost::math::interpolators::cardinal_cubic_b_spline<double> f1, boost::math::interpolators::cardinal_cubic_b_spline<double> f2, double start, double end, int e_threshold, double threshold) {

	std::vector<double> v;
	std::vector<std::vector<double>> list_v;

	for (double x = start; x < end; x++) {

		v = flow_1d_v0(iterations, list_v0, x, f1, f2, e_threshold, threshold);

		list_v.push_back(v);
	}

	return list_v;
}





