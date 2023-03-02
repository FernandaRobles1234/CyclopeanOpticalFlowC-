#include "test_functions.h"
#include <cmath>

LineFunc::LineFunc(double m, double c, double s) : m_m(m), m_c(c), m_s(s)
{
}

double LineFunc::operator()(double x) const
{
	return m_m * (x+m_s) + m_c;
}

double LineFunc::prime(double x) const
{
    return m_m;
}

double LineFunc::double_prime(double x) const
{
    return 0;
}




SinFunc::SinFunc(double s) : m_s(s)
{
}

double SinFunc::operator()(double x) const
{
    return std::sin(x - m_s);
}

double SinFunc::prime(double x) const
{
    return std::cos(x - m_s);
}

double SinFunc::double_prime(double x) const
{
    return -std::sin(x - m_s);
}