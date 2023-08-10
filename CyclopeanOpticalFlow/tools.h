#pragma once
#include <vector>
#include <random>

#define TOLERANCE 0.00001
#define FIXED_SEED 123

template<typename T>
using Matrix2D = std::vector<std::vector<T>>;

template<typename T>
Matrix2D<T> uniformDistribution2D(int size, T v1, T v2, bool testingMode) {

    Matrix2D<T> list_v0;
    list_v0.reserve(size);

    // Create a random number generator
    std::mt19937 gen;
    if (testingMode == true) {
        gen = std::mt19937(FIXED_SEED);
    }
    else {
        std::random_device rd;
        gen = std::mt19937(rd());
    }


    // Create a uniform real distribution object
    std::uniform_real_distribution<T> dist(0, v2);

    T x, y, distance;

    // Generate random points until we find one within the unit circle
    for (int i = 0; i < size; i++) {

        do {
            // Generate a random number between v1 and v2
            x = dist(gen);
            y = dist(gen);

            distance = (x + y);

            // Repeate while the generation is not valid
        } while (!(distance >= v1 && distance <= v2));

        list_v0.push_back({ x,y });
    }

    return list_v0;
}

template<typename T>
 static bool isEqual(T x, T y)
 {
     return fabs(x - y) < TOLERANCE;
 }

 template<typename T>
 T mean(T data[], int n) {
     T sum = 0;
     for (int i = 0; i < n; i++) {
         sum += data[i];
     }
     return sum / n;
 }

 template<typename T>
 T variance(T data[], int n) {
     T meanValue = mean(data, n);
     T temp = 0;

     for (int i = 0; i < n; i++) {
         temp += (data[i] - meanValue) * (data[i] - meanValue);
     }
     return temp / (n - 1);
 }

 template<typename T>
 T covariance(T data1[], T data2[], int n) {
     T mean1 = mean(data1, n);
     T mean2 = mean(data2, n);
     T temp = 0;
     for (int i = 0; i < n; i++) {
         temp += (data1[i] - mean1) * (data2[i] - mean2);
     }
     return temp / (n - 1);
 }

 template<typename T>
 T pearsonCorrelation(T data1[], T data2[], int n) {
     return covariance(data1, data2, n) / (sqrt(variance(data1, n)) * sqrt(variance(data2, n)));
 }

 template<typename T>
 T L2Norm(const std::vector<T>& v) {
     T sum = 0;
     for (T x : v) {
         sum += x * x;
     }
     return sqrt(sum);
 }

