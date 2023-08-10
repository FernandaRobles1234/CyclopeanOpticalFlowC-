#include "pch.h"


#include "../CyclopeanOpticalFlow/tools.h"
#include "../CyclopeanOpticalFlow/pyramid.h"
#include "../CyclopeanOpticalFlow/Image.h"
 
#include "../CyclopeanOpticalFlow/displayResults.h"

//TODO: Do negative numbers Test
TEST(tools, uniformDistribution2DTest1) {
	int size = 10;

	
	float minNumber = 2.0;
	float maxNumber = 5.0;
	
	Matrix2D<float> listV0;
	listV0.reserve(size);
	
	listV0= uniformDistribution2D(size, minNumber, maxNumber, true);

	bool criteria = true;

	for (std::vector<float> v0 : listV0) {
		if (minNumber <= v0[0]+v0[1] && v0[0]+v0[1] <= maxNumber) {
		}
		else {
			criteria = false;
			break;
		}
	}

	EXPECT_TRUE(criteria);
}

TEST(tools, pearsonCorrelationTest1) {
	float r = 0.0;

	std::vector<float> x = { 1, 2, 3, 4, 5 };
	std::vector<float> y = { 2, 4, 6, 8, 10 };

	r = pearsonCorrelation(&x[0], &y[0], (int)x.size());

	EXPECT_TRUE(isEqual((float)1.0, r));
}

TEST(tools, pearsonCorrelationTest2) {
	float r = 0.0;

	std::vector<float> x = { 1, 2, 3, 4, 5 };
	std::vector<float> y = { 3, 5, 6, 7, 9 };

	r = pearsonCorrelation(&x[0], &y[0], (int)x.size());

	EXPECT_TRUE((float)0.0 < r);
}

TEST(tools, L2NormTest1) {
	std::vector<float> v = { 1, 2, 3, 4, 5 };
	float norm = 0;

	norm = L2Norm(v);


	EXPECT_TRUE(isEqual((float)7.416198487 , norm));
}

TEST(pyramid, padVectorTest1) {
	std::vector<float> v = { 1, 2, 3, 4, 5 };
	int padStart = 1;
	int padEnd = 1;
	int startSize = (int)v.size() + padStart + padEnd;

	padVector(v, padStart, padEnd);


	EXPECT_TRUE(isEqual((int)v.size(), startSize));
}

TEST(pyramid, generatePyramidRepresentationTest1) {
	std::vector<float> v = { 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.0993805, 0.90062, 1., 1., 1., 
		1., 1., 1., 0.90062, 0.0993805, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. };

	//TODO: Check if they are at least 5 points for the interpolation
	std::vector<fun<float>> vf = generatePyramidRepresentation(v, 1);


	display_function(vf[0], vf[1], 0, (int)v.size());


	EXPECT_TRUE(true);
}

TEST(pyramid, generatePyramidRepresentationTest2) {
	std::vector<float> v = { 43, 102, 90, 88, 65, 88, 60, 64, 63, 120, 55, 78, 89, 85, 53, 34, 68,
   68, 46, 101, 39, 130, 107, 81, 51, 28, 73, 52, 60, 73, 28, 33, 159,
   63, 56, 98, 66, 43, 28, 30, 28, 29, 28, 39, 122, 74, 78, 79, 92,
  92, 78, 61, 53, 48, 43, 223, 172, 204, 83, 132, 96, 52, 41, 37, 110,
   166, 85, 45, 50, 44, 112, 47, 43, 34, 53, 50, 48, 93, 86, 104, 78,
  82, 45, 43, 33, 33, 37, 36, 31, 34, 152, 252, 34, 34, 96, 104, 255,
  224, 46, 34, 34, 37, 255, 255, 240, 81 };

	//TODO: Check if they are at least 5 points for the interpolation
	std::vector<fun<float>> vf = generatePyramidRepresentation(v, 1);


	display_function(vf[0], vf[1], 0, (int)v.size());


	EXPECT_TRUE(true);
}

TEST(Image, generatePyramidFunctionTest1) {
	std::vector<std::vector<float>> v = { { 43, 102, 90, 88, 65, 88, 60, 64, 63, 120, 55, 78, 89, 85, 53, 34, 68,
   68, 46, 101, 39, 130, 107, 81, 51, 28, 73, 52, 60, 73, 28, 33, 159,
   63, 56, 98, 66, 43, 28, 30, 28, 29, 28, 39, 122, 74, 78, 79, 92,
  92, 78, 61, 53, 48, 43, 223, 172, 204, 83, 132, 96, 52, 41, 37, 110,
   166, 85, 45, 50, 44, 112, 47, 43, 34, 53, 50, 48, 93, 86, 104, 78,
  82, 45, 43, 33, 33, 37, 36, 31, 34, 152, 252, 34, 34, 96, 104, 255,
  224, 46, 34, 34, 37, 255, 255, 240, 81 } };

	cof::Image<float> im(v);
	std::vector<fun<float>> imfun= im.generatePyramidFunction(0, 1);

	display_function(imfun[0], imfun[1], 0, (int)v[0].size());

	EXPECT_TRUE(true);
}

TEST(cyclopeanOpticalFlow, generatePyramidFunctionMatrixTest1) {
	std::vector<std::vector<float>> v1 = { { 43, 102, 90, 88, 65, 88, 60, 64, 63, 120, 55, 78, 89, 85, 53, 34, 68,
		68, 46, 101, 39, 130, 107, 81, 51, 28, 73, 52, 60, 73, 28, 33, 159,
		63, 56, 98, 66, 43, 28, 30, 28, 29, 28, 39, 122, 74, 78, 79, 92,
		92, 78, 61, 53, 48, 43, 223, 172, 204, 83, 132, 96, 52, 41, 37, 110,
		166, 85, 45, 50, 44, 112, 47, 43, 34, 53, 50, 48, 93, 86, 104, 78,
		82, 45, 43, 33, 33, 37, 36, 31, 34, 152, 252, 34, 34, 96, 104, 255,
		224, 46, 34, 34, 37, 255, 255, 240, 81 } };

	std::vector<std::vector<float>> v2 = { {69, 117, 100, 83, 82, 72, 90, 59, 152, 123, 60, 93, 77, 97, 84, 34, 
		61, 72, 67, 42, 36, 56, 101, 51, 109, 34, 74, 66, 54, 61, 28, 36, 34,
		70, 175, 121, 94, 51, 59, 40, 28, 28, 28, 28, 39, 136, 72, 74, 74,
		113, 108, 76, 54, 53, 45, 207, 169, 154, 222, 57, 125, 57, 35, 33,
		145, 145, 134, 78, 65, 50, 40, 101, 37, 46, 56, 60, 37, 45, 53, 64,
		39, 45, 112, 32, 71, 46, 41, 47, 34, 28, 40, 132, 119, 31, 32, 172, 
		255, 221, 84, 28, 28, 37, 255, 254, 255, 43} };


	cof::Image<float> im1(v1);
	std::vector<std::vector<fun<float>>> imfun1 = im1.generatePyramidFunctionMatrix(1);

	cof::Image<float> im2(v2);
	std::vector<std::vector<fun<float>>> imfun2 = im2.generatePyramidFunctionMatrix(1);

	display_function(imfun1[0][0], imfun2[0][0], 0, (int)v1[0].size());

	EXPECT_TRUE(true);
}