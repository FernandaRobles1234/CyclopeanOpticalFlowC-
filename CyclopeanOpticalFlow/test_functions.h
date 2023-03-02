#pragma once

class LineFunc {
public:
    LineFunc(double m, double c, double s);

    double operator()(double x) const;
    double prime(double x) const;
    double double_prime(double x) const;

private:
    double m_m;
    double m_c;
    double m_s;
};

class SinFunc {
public:
    SinFunc(double s);

    double operator()(double x) const;
    double prime(double x) const;
    double double_prime(double x) const;

private:
    double m_s;
};
