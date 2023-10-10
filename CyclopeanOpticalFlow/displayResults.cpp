#include <vector>
#include <iostream>
#include <boost/math/interpolators/cardinal_cubic_b_spline.hpp>
#include "matplotlibcpp.h"


//----------------------------------------------------Display Functions Optical Flow----------------------------------------------------

int displayFlowLine(std::vector<std::vector<float>>& v, boost::math::interpolators::cardinal_cubic_b_spline<float> f1, boost::math::interpolators::cardinal_cubic_b_spline<float> f2, int start, int end) {

	//We create x vector
	float step = 0.5;
	int inverse_step = 2;
	std::vector<float> x(end * (1 * inverse_step) - start * (1 * inverse_step));
	float n = start;
	for (int i = 0; i < x.size(); i++) {
		x[i] = n;
		n = n + step;
	}


	//We create y1 vector
	std::vector<float> y1(x.size());
	for (int i = 0; i < y1.size(); i++) {
		y1[i] = f1(x[i]);
	}

	//We create y2 vector
	std::vector<float> y2(x.size());
	for (int i = 0; i < y2.size(); i++) {
		y2[i] = f2(x[i]);
	}

	matplotlibcpp::plot(x, y1);
	matplotlibcpp::plot(x, y2);

	// Flow vector
	float y_c;
	std::vector<float> x_p;
	std::vector<float> y_p;
	std::vector<float> x_dot;
	std::vector<float> y_dot;

	//The minus one is due to the fact that odd numbers are decreased by one
	for (float p = start; p < end - 1; p++) {

		y_c = (f1(p) + f2(p)) / 2;
		y_p = { y_c, y_c, y_c };


		x_p = { p - v[p - start][0], (float)p, p + v[p - start][1] };

		if (v[p][3] == 5) {
			matplotlibcpp::plot(x_p, y_p, "green");
		}
		else if (v[p][3] == 0) {
			matplotlibcpp::plot(x_p, y_p, "black");
		}
		else if (v[p][3] == 1) {
			matplotlibcpp::plot(x_p, y_p, "purple");
		}
		else if (v[p][3] == 2) {
			matplotlibcpp::plot(x_p, y_p, "red");
		}
		else if (v[p][3] == 3) {
			matplotlibcpp::plot(x_p, y_p, "yellow");
		}
		else {
			matplotlibcpp::plot(x_p, y_p, "pink");
		}


		//Attempt of dot
		y_dot = { y_c, y_c };
		x_dot = { p - 0.02f, p + 0.02f };
		matplotlibcpp::plot(x_dot, y_dot, "r");

	}

	matplotlibcpp::show();

	return 0;
}

int displayFlowPoint(float p0, std::vector<float>& v, boost::math::interpolators::cardinal_cubic_b_spline<float> f1, boost::math::interpolators::cardinal_cubic_b_spline<float> f2, int start, int end) {
	//TODO: This could be replaced by display flow line?
	//We create x vector
	float step = 0.5;
	int inverse_step = 2;
	std::vector<float> x(end * (1 * inverse_step) - start * (1 * inverse_step));
	float n = start;
	for (int i = 0; i < x.size(); i++) {
		x[i] = n;
		n = n + step;
	}


	//We create y1 vector
	std::vector<float> y1(x.size());
	for (int i = 0; i < y1.size(); i++) {
		y1[i] = f1(x[i]);
	}

	//We create y2 vector
	std::vector<float> y2(x.size());
	for (int i = 0; i < y2.size(); i++) {
		y2[i] = f2(x[i]);
	}

	matplotlibcpp::plot(x, y1);
	matplotlibcpp::plot(x, y2);

	// Flow vector
	float y_c;
	std::vector<float> x_p;
	std::vector<float> y_p;
	std::vector<float> x_dot;
	std::vector<float> y_dot;

	//The minus one is due to the fact that odd numbers are decreased by one
	float p = p0;

	y_c = (f1(p) + f2(p)) / 2;
	y_p = { y_c, y_c, y_c };


	x_p = { p - v[0], (float)p, p + v[1] };

	if (v[3] == 5) {
		matplotlibcpp::plot(x_p, y_p, "green");
	}
	else if (v[3] == 0) {
		matplotlibcpp::plot(x_p, y_p, "black");
	}
	else if (v[3] == 1) {
		matplotlibcpp::plot(x_p, y_p, "purple");
	}
	else if (v[3] == 2) {
		matplotlibcpp::plot(x_p, y_p, "red");
	}
	else if (v[3] == 3) {
		matplotlibcpp::plot(x_p, y_p, "yellow");
	}
	else {
		matplotlibcpp::plot(x_p, y_p, "pink");
	}


	//Attempt of dot
	y_dot = { y_c, y_c };
	x_dot = { p - 0.02f, p + 0.02f };
	matplotlibcpp::plot(x_dot, y_dot, "r");

	matplotlibcpp::show();

	return 0;
}

void display_function(boost::math::interpolators::cardinal_cubic_b_spline<float> f1, boost::math::interpolators::cardinal_cubic_b_spline<float> f2, float start, float end, float step) {
	if (step == 0) {
		std::cout << "steps==0" << std::endl;
		std::cin.get();
	}

	std::vector<float> x(end * (1 / step) - start * (1 / step));
	float n = start;

	for (int i = 0; i < x.size(); i++) {
		x[i] = n;
		n = n + step;
	}

	std::vector<float> y1(x.size());
	for (int i = 0; i < y1.size(); i++) {
		y1[i] = f1(x[i]);
	}

	std::vector<float> y2(x.size());
	for (int i = 0; i < y2.size(); i++) {
		y2[i] = f2(x[i]);
	}

	matplotlibcpp::plot(x, y1);
	matplotlibcpp::plot(x, y2);
	matplotlibcpp::show();

}

int display_vector(std::vector<double> f1, double f1_start, double f1_end, double f1_step, std::vector<double> f2, double f2_start, double f2_end, double f2_step) {
	if (f1_step == 0 || f2_step == 0) {
		std::cout << "steps==0" << std::endl;
		std::cin.get();
		return -1;
	}

	// creating first data, f1_x and y1 (change to f1_y)
	std::vector<double> f1_x(f1.size());
	double f1_n = f1_start;

	for (int i = 0; i < f1_x.size(); i++) {
		f1_x[i] = f1_n;
		f1_n = f1_n + f1_step;
	}

	std::vector<double> y1(f1_x.size());
	for (int i = 0; i < y1.size(); i++) {
		y1[i] = f1[i];
	}

	// creating first data, f2_x and y2 (change to f2_y)
	std::vector<double> f2_x(f2.size());
	double f2_n = f2_start;

	for (int i = 0; i < f2_x.size(); i++) {
		f2_x[i] = f2_n;
		f2_n = f2_n + f2_step;
	}

	std::vector<double> y2(f2_x.size());
	for (int i = 0; i < y2.size(); i++) {
		y2[i] = f2[i];
	}

	matplotlibcpp::plot(f1_x, y1);
	matplotlibcpp::plot(f2_x, y2);
	matplotlibcpp::show();

}
