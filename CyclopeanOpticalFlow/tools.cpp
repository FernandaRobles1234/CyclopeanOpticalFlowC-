#include <iostream>
#include <random>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "tools.h"

//TODO: Make this a global constant for cyclopeanOpticalFLow as well
const unsigned int FIXED_SEED = 123; // You can change this value to get different random sequences

std::vector <std::vector<double>> uniformDistribution2d(int size ,double v1, double v2) {

    std::vector<std::vector<double>> list_v0;
    list_v0.reserve(size);

    // Create a random number generator
    //std::random_device rd;
    std::mt19937 gen(FIXED_SEED);

    // Create a uniform real distribution object
    std::uniform_real_distribution<double> dist(v1, v2);

    double x, y, distance;

    // Generate random points until we find one within the unit circle
    for (int i = 0; i < size; i++) {
        
         do{
            // Generate a random number between v1 and v2
            x = dist(gen);
            y = dist(gen);

            distance = (x + y);

        // Repeate while the generation is not valid
        } while (!(distance >= v1 && distance <= v2));

        list_v0.push_back({x,y});
    }
    
    return list_v0;
}






