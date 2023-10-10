#pragma once
#include <vector>
#include <random>

// Define precision thresholds for comparing floating point numbers
#define TOLERANCE 0.00001
#define TOLERANCEL 0.5

// Fixed seed value for deterministic random number generation in testing scenarios
#define FIXED_SEED 123

// Alias for a 2D matrix using vectors.
template<typename T>
using Matrix2D = std::vector<std::vector<T>>;


// Generates a 2D matrix of random points (x, y) within a specified range.
// Each point's (x + y) is ensured to lie between [v1, v2].
// Allows for deterministic generation using a fixed seed for testing.
template<typename T>
Matrix2D<T> uniformDistribution2D(int size, T v1, T v2, bool testingMode= false) {

    Matrix2D<T> list_v0;
    list_v0.reserve(size);

    // Mersenne twister random number generator
    std::mt19937 gen;
    if (testingMode == true) {
        gen = std::mt19937(FIXED_SEED); // Use fixed seed for testing
    }
    else {
        std::random_device rd; // Non-deterministic seed
        gen = std::mt19937(rd());
    }


    // Uniform real distribution between 0 and v2
    std::uniform_real_distribution<T> dist(0, v2);

    T x, y, distance;

    // Fill the matrix with valid points
    for (int i = 0; i < size; i++) {

        do {
            x = dist(gen);
            y = dist(gen);

            distance = (x + y);

        } while (!(distance >= v1 && distance <= v2));

        list_v0.push_back({ x,y });
    }

    return list_v0;
}

// Compares two numbers for equality within a large tolerance.
template<typename T>
 static bool isEqualL(T x, T y)
 {
     return fabs(x - y) < TOLERANCEL;
 }

 // Compares two numbers for equality within a smaller tolerance.
 template<typename T>
 static bool isEqual(T x, T y)
 {
     return fabs(x - y) < TOLERANCE;
 }

 // Calculates the mean of a dataset.
 template<typename T>
 T mean(T data[], int n) {
     T sum = 0;
     for (int i = 0; i < n; i++) {
         sum += data[i];
     }
     return sum / n;
 }

 // Calculates the variance of a dataset.
 template<typename T>
 T variance(T data[], int n) {
     T meanValue = mean(data, n);
     T temp = 0;

     for (int i = 0; i < n; i++) {
         temp += (data[i] - meanValue) * (data[i] - meanValue);
     }
     return temp / (n - 1);
 }

 // Calculates the covariance between two datasets.
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

 // Calculates the Pearson correlation coefficient between two datasets.
 template<typename T>
 T pearsonCorrelation(T data1[], T data2[], int n) {
     return covariance(data1, data2, n) / (sqrt(variance(data1, n)) * sqrt(variance(data2, n)));
 }

 // Calculates the L2 norm (Euclidean norm) of a vector.
 template<typename T>
 T L2Norm(const std::vector<T>& v) {
     T sum = 0;
     for (T x : v) {
         sum += x * x;
     }
     return sqrt(sum);
 }

