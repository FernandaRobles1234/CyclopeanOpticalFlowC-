#include <vector>
#include <iostream>
#include <boost/math/interpolators/cardinal_cubic_b_spline.hpp>
#include "matplotlibcpp.h"


//----------------------------------------------------Display Functions Optical Flow----------------------------------------------------

int displayFlowLine(std::vector<std::vector<double>>& v, boost::math::interpolators::cardinal_cubic_b_spline<double> f1, boost::math::interpolators::cardinal_cubic_b_spline<double> f2, int start, int end) {

	//We create x vector
	double step = 0.5;
	int inverse_step = 2;
	std::vector<double> x(end * (1 * inverse_step) - start * (1 * inverse_step));
	double n = start;
	for (int i = 0; i < x.size(); i++) {
		x[i] = n;
		n = n + step;
	}


	//We create y1 vector
	std::vector<double> y1(x.size());
	for (int i = 0; i < y1.size(); i++) {
		y1[i] = f1(x[i]);
	}

	//We create y2 vector
	std::vector<double> y2(x.size());
	for (int i = 0; i < y2.size(); i++) {
		y2[i] = f2(x[i]);
	}

	matplotlibcpp::plot(x, y1);
	matplotlibcpp::plot(x, y2);

	// Flow vector
	double y_c;
	std::vector<double> x_p;
	std::vector<double> y_p;
	std::vector<double> x_dot;
	std::vector<double> y_dot;

	//The minus one is due to the fact that odd numbers are decreased by one
	for (int p = start; p < end - 1; p++) {

		y_c = (f1(p) + f2(p)) / 2;
		y_p = { y_c, y_c, y_c };


		x_p = { p - v[p - start][0], (double)p, p + v[p - start][1] };

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
		x_dot = { p - 0.02, p + 0.02 };
		matplotlibcpp::plot(x_dot, y_dot, "r");

	}

	matplotlibcpp::show();

	return 0;
}

int display_function(boost::math::interpolators::cardinal_cubic_b_spline<double> f1, boost::math::interpolators::cardinal_cubic_b_spline<double> f2, double start, double end, double step) {
	if (step == 0) {
		std::cout << "steps==0" << std::endl;
		std::cin.get();
		return -1;
	}

	std::vector<double> x(end * (1 / step) - start * (1 / step));
	double n = start;

	for (int i = 0; i < x.size(); i++) {
		x[i] = n;
		n = n + step;
	}

	std::vector<double> y1(x.size());
	for (int i = 0; i < y1.size(); i++) {
		y1[i] = f1(x[i]);
	}

	std::vector<double> y2(x.size());
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
