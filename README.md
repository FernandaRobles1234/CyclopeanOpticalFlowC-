# Cyclopean Optical Flow
## By: Fernanda Robles

## Table of Contents

- [Project Description](#project-description)
- [Usage](#usage)

## Project Description

Cyclopean Optical Flow is a novel approach to determine the apparent motion patterns in stereo imagery. This C++ implementation aims to harness the efficiency and power of C++ to provide real-time processing of stereo images to extract valuable information regarding their motion dynamics.

Features:
Real-time Processing:

Process stereo images swiftly due to C++'s performance benefits.
Depth Perception:

Extract depth information from stereo images, offering a 3D understanding of the scene.
Motion Estimation:

Identify and estimate motion trajectories, helping in object tracking and scene analysis.
Dynamic Adjustment:

The application allows users to adjust various parameters for custom analysis.
Robust Error Handling:

The program checks for incorrect file paths, ensuring users are alerted to potential mistakes.

## Usage

This implementation is still in development, but here is an example of how to obtain results or run a test for two lines, v1 and v2.

```cpp
// Define the size of our matrix
int size = 10;

// Set the range for the uniform distribution
float minNumber = 0.0;
float maxNumber = 2.0;

// Create a 2D matrix to store float values
Matrix2D<float> listV0;

// Reserve space in memory for our matrix
listV0.reserve(size);

// Fill our 2D matrix with a uniform distribution of float values 
listV0 = uniformDistribution2D(size, minNumber, maxNumber, true);

// Define two vector functions for our pyramid functions
std::vector<float> v1 = { /*...*/ };  // truncated for brevity
std::vector<float> v2 = { /*...*/ };  // truncated for brevity

// Generate pyramid function levels for our vectors
std::vector<fun<float>> f1 = generatePyramidFunctionLevels(v1, 0);
std::vector<fun<float>> f2 = generatePyramidFunctionLevels(v2, 0);

// Define a 2D matrix for storing the results
Matrix2D<float> vRow;

// Set threshold values for processing 
int e_threshold = 0;
float threshold = 0.001;

// Define a lambda function for further operations (this example always returns true)
auto lambda = [](float v1, float v2) -> bool {
    return true;
};


// Save results in vRow
vRow = cyclopeanOpticalFlowRow(lambda, listV0, f1, f2, e_threshold, threshold, 0.0f, (float)v1.size());

	displayFlowLine(vRow, f1[0], f2[0], 0.0f, (float)v1.size());

```


