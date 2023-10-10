#include "pch.h"


#include "../CyclopeanOpticalFlow/tools.h"
#include "../CyclopeanOpticalFlow/pyramid.h"
#include "../CyclopeanOpticalFlow/Image.h"
#include "../CyclopeanOpticalFlow/cyclopeanOpticalFlow.h"
 
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
	std::vector<fun<float>> vf = generatePyramidFunctionLevels(v, 1);


	//display_function(vf[0], vf[1], 0, (int)v.size());


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
	std::vector<fun<float>> vf = generatePyramidFunctionLevels(v, 1);


	//display_function(vf[0], vf[1], 0, (int)v.size());


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
	std::vector<fun<float>> imfun= im.generatePyramidFunctions(0, 1);

	//display_function(imfun[0], imfun[1], 0, (int)v[0].size());

	EXPECT_TRUE(true);
}
TEST(Image, generatePyramidFunctionMatrixTest1) {
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

	//display_function(imfun1[0][1], imfun2[0][1], 0, (int)v1[0].size());

	EXPECT_TRUE(true);
}
TEST(cyclopeanOpticalFlow, newValuesTest1) {
	int size = 10;

	float minNumber = 2.0;
	float maxNumber = 5.0;

	Matrix2D<float> listV0;
	listV0.reserve(size);

	listV0 = uniformDistribution2D(size, minNumber, maxNumber, true);

	std::vector<float> v0 = { 0.0, 0.0, 0.0, 0.0 };
	int e_threshold = 0;
	Matrix2D<float> newListV0;

	newListV0= new_values(listV0, size, v0, e_threshold);

	bool criteria = true;

	for (size_t i = 0; i < newListV0.size(); i++) {
		for (size_t j = 0; j < newListV0[i].size(); j++) {
			if (isEqual(newListV0[i][j], listV0[i][j])) {
			}
			else {
				criteria = false;
				break;
			}
		}
		
	}

	EXPECT_TRUE(criteria);
}
TEST(cyclopeanOpticalFlow, newValuesTest2) {
	int size = 10;

	float minNumber = 2.0;
	float maxNumber = 5.0;

	Matrix2D<float> listV0;
	listV0.reserve(size);

	listV0 = uniformDistribution2D(size, minNumber, maxNumber, true);

	std::vector<float> v0 = { 0.0, 0.0, 1.0, 0.0};
	int e_threshold = 0;
	Matrix2D<float> newListV0;

	newListV0 = new_values(listV0, size, v0, e_threshold);

	bool criteria = true;

	for (size_t i = 0; i < newListV0.size(); i++) {
		for (size_t j = 0; j < newListV0[i].size(); j++) {
			if (isEqual(newListV0[i][j], 0.0f)) {
			}
			else {
				criteria = false;
				break;
			}
		}
	}

	EXPECT_TRUE(criteria);
}
TEST(cyclopeanOpticalFlow, newValuesTest3) {
	float minNumber = 2.0f;
	float maxNumber = 5.0f;

	int size = 10;

	Matrix2D<float> listV0;
	listV0.reserve(size);

	listV0 = uniformDistribution2D(size, minNumber, maxNumber, true);

	std::vector<float> v0 = { 3.0f, 3.0f, 0, 0.0f };
	int e_threshold = 0;
	Matrix2D<float> newListV0;
	newListV0.reserve(size);

	newListV0 = new_values(listV0, size, v0, e_threshold, true);

	bool criteria = true;
	float sum= 0;


	for (size_t i = 0; i < newListV0.size(); i++) {
		for (size_t j = 0; j < newListV0[i].size(); j++) {
			sum += newListV0[i][j];
		}

		if (isEqualL(sum, 6.0f)) {
		}
		else {
			criteria = false;
			break;
		}
		sum = 0;
	}

	EXPECT_TRUE(criteria);
}
TEST(cyclopeanOpticalFlow, pickNewValuesTest1) {
	std::vector<float> v0;
	Matrix2D<float> listV0 = { { 3.0, 2.0, 2.0, 5.0 },
		{ 2.0, 3.0, 2.0, 5.0 },
		{ 3.0, 3.0, 1.0, 5.0 },
		{ 7.0, 3.0, 1.0, 5.0 },
		{ 0.0, 1.0, 5.0, 5.0 } };

	auto lambda = [](float v1, float v2) -> bool {
		return (v1 * v2 > 0 && v1 + v2 >= 0 && v1 + v2 <= 5);
	};

	v0 = pickNewValues(listV0, 0, lambda);

	bool criteria = isEqualL(v0[0], 0.0f) && isEqualL(v0[1], 0.0f);
	
	EXPECT_TRUE(criteria);
}
TEST(cyclopeanOpticalFlow, pickNewValuesTest2) {
	std::vector<float> v0;
	Matrix2D<float> listV0 = { { 3.0, 3.0, 0.0, 0.0 },
		{ -2.0, -3.0, 0.0, 0.0 },
		{ -3.0, 5.0, 0.0, 0.0 },
		{ 7.0, 0.0, 0.0, 0.0 },
		{ 0.000001, 0.000002, 0.0, 0.0 } };

	auto lambda = [](float v1, float v2)  -> bool {
		return (v1 * v2 > 0 && v1 + v2 >= 0 && v1 + v2 <= 5);
	};

	v0 = pickNewValues(listV0, 0, lambda);

	bool criteria = isEqualL(v0[0], 0.0f) && isEqualL(v0[1], 0.0f);

	EXPECT_TRUE(criteria);
}
TEST(cyclopeanOpticalFlow, pickNewValuesTest3) {
	std::vector<float> v0;
	Matrix2D<float> listV0 = { {2.0, 2.0, 0.0, 0.0}, 
		{2.5, 2.5, 0.0, 5.0},
		{5.0, 0.0, 0.0, 5.0} };

	auto lambda = [](float v1, float v2) -> bool {
		return (v1 * v2 >= 0.0 && v1 + v2 >= 0.0 && v1 + v2 <= 5.0);
	};


	v0 = pickNewValues(listV0, 0, lambda);

	bool criteria = isEqualL(v0[0], 2.5f) && isEqualL(v0[1], 2.5f);

	EXPECT_TRUE(criteria);
}
TEST(cyclopeanOpticalFlow, pickNewValuesTest4) {
	std::vector<float> v0;
	Matrix2D<float> listV0 = { {2.0, 2.0, 0.0, 0.0},
		{2.5, 2.5, 2.0, 5.0},
		{5.0, 0.0, 1.0, 5.0},
		{0.0, 5.0, 0.0, 5.0} };

	int e_threshold = 1;

	auto lambda = [](float v1, float v2)  -> bool {
		return (v1 * v2 >= 0.0 && v1 + v2 >= 0.0 && v1 + v2 <= 5.0);
	};

	v0 = pickNewValues(listV0, e_threshold, lambda);

	bool criteria = isEqualL(v0[0], 5.0f) && isEqualL(v0[1], 0.0f);

	EXPECT_TRUE(criteria);
}
TEST(cyclopeanOpticalFlow, upgrade_1dTest1) {
	std::vector<float> v1 = { 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.0993805, 0.90062, 1., 1., 1.,
		1., 1., 1., 0.90062, 0.0993805, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. };
	std::vector<float> v2 = { 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.0993805, 0.90062, 1., 1., 1.,
		1., 1., 1., 0.90062, 0.0993805, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. };

	std::vector<fun<float>> f1 = generatePyramidFunctionLevels(v1, 0);
	std::vector<fun<float>> f2 = generatePyramidFunctionLevels(v2, 0);

	//display_function(f1[0], f2[0], 0, (int)v1.size());

	std::vector<float> v0 = {0.0, 0.0, 0.0, 0.0};
	float p0 = 10;
	int e_threshold = 0;
	float threshold = 0.001;

	v0= upgrade_1d(v0, p0, f1[0], f2[0], e_threshold, threshold);
	
	Matrix2D<float> v0List = { v0 };

	//displayFlowPoint(p0, v0, f1[0], f2[0], 0, (int)v1.size());

	EXPECT_TRUE(true);
}
TEST(cyclopeanOpticalFlow, upgrade_1dTest2) {
	std::vector<float> v1 = { 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.0993805, 0.90062, 1., 1., 1.,
		1., 1., 1., 0.90062, 0.0993805, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. };
	std::vector<float> v2 = { 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.0993805, 0.90062, 1., 1., 1.,
		1., 1., 1., 0.90062, 0.0993805, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. };

	std::vector<fun<float>> f1 = generatePyramidFunctionLevels(v1, 0);
	std::vector<fun<float>> f2 = generatePyramidFunctionLevels(v2, 0);


	std::vector<float> v0 = { 0.0, 0.0, 0.0, 0.0 };
	float p0 = 15;
	int e_threshold = 0;
	float threshold = 0.001;

	v0 = upgrade_1d(v0, p0, f1[0], f2[0], e_threshold, threshold);

	Matrix2D<float> v0List = { v0 };

	//displayFlowPoint(p0, v0, f1[0], f2[0], 0, (int)v1.size());

	EXPECT_TRUE(true);
}
TEST(cyclopeanOpticalFlow, upgrade_1dTest3) {
	std::vector<double> v1 = { 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.0993805, 0.90062, 1., 1., 1.,
		1., 1., 1., 0.90062, 0.0993805, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. };
	std::vector<double> v2 = { 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.0993805, 0.90062, 1., 1., 1.,
		1., 1., 1., 0.90062, 0.0993805, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. };

	std::vector<fun<double>> f1 = generatePyramidFunctionLevels(v1, 0);
	std::vector<fun<double>> f2 = generatePyramidFunctionLevels(v2, 0);


	std::vector<double> v0 = { 0.0, 0.0, 0.0, 0.0 };
	double p0 = 15;
	int e_threshold = 0;
	double threshold = 0.001;

	v0 = upgrade_1d(v0, p0, f1[0], f2[0], e_threshold, threshold);

	Matrix2D<double> v0List = { v0 };

	//displayFlowPoint(p0, v0, f1[0], f2[0], 0, (int)v1.size());

	EXPECT_TRUE(true);
}
TEST(cyclopeanOpticalFlow, pyr_flow_1d_v0Test1) {
	int size = 10;

	double minNumber = 0.0;
	double maxNumber = 2.0;

	Matrix2D<double> listV0;
	listV0.reserve(size);

	listV0 = uniformDistribution2D(size, minNumber, maxNumber, true);

	std::vector<double> v1 = { 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.0993805, 0.90062, 1., 1., 1.,
		1., 1., 1., 0.90062, 0.0993805, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. };
	std::vector<double> v2 = { 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.0993805, 0.90062, 1., 1., 1.,
		1., 1., 1., 0.90062, 0.0993805, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. };

	std::vector<fun<double>> f1 = generatePyramidFunctionLevels(v1, 0);
	std::vector<fun<double>> f2 = generatePyramidFunctionLevels(v2, 0);


	std::vector<double> v0 = { 0.0f, 0.0f, 0.0f, 0.0f };
	double p0 = 10;
	int e_threshold = 0;
	double threshold = 0.001;

	auto lambda = [](double v1, double v2) -> bool {
		return true;
	};

	v0= pyr_flow_1d_v0(lambda,
		listV0, p0, f1, f2, e_threshold, threshold);

	//displayFlowPoint(p0, v0, f1[0], f2[0], 0, (int)v1.size());

	EXPECT_TRUE(true);
}

TEST(cyclopeanOpticalFlow, pyr_flow_1d_v0Test2) {
	int size = 10;

	float minNumber = 0.0;
	float maxNumber = 2.0;

	Matrix2D<float> listV0;
	listV0.reserve(size);

	listV0 = uniformDistribution2D(size, minNumber, maxNumber, true);

	std::vector<float> v1 = { 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.0993805, 0.90062, 1., 1., 1.,
		1., 1., 1., 0.90062, 0.0993805, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. };
	std::vector<float> v2 = { 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.0993805, 0.90062, 1., 1., 1.,
		1., 1., 1., 0.90062, 0.0993805, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. };

	std::vector<fun<float>> f1 = generatePyramidFunctionLevels(v1, 0);
	std::vector<fun<float>> f2 = generatePyramidFunctionLevels(v2, 0);


	std::vector<float> v0 = { 0.0f, 0.0f, 0.0f, 0.0f };
	float p0 = 10;
	int e_threshold = 0;
	float threshold = 0.001;

	auto lambda = [](float v1, float v2) -> bool {
		return true;
	};

	v0 = pyr_flow_1d_v0(lambda,
		listV0, p0, f1, f2, e_threshold, threshold);

	//displayFlowPoint(p0, v0, f1[0], f2[0], 0, (int)v1.size());

	EXPECT_TRUE(true);
}

TEST(cyclopeanOpticalFlow, pyr_flow_1d_v0Test3) {
	int size = 10;

	float minNumber = 0.0;
	float maxNumber = 2.0;

	Matrix2D<float> listV0;
	listV0.reserve(size);

	listV0 = uniformDistribution2D(size, minNumber, maxNumber, true);

	std::vector<float> v1 = { 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.0993805, 0.90062, 1., 1., 1.,
		1., 1., 1., 0.90062, 0.0993805, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. };
	std::vector<float> v2 = { 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.0993805, 0.90062, 1., 1., 1.,
		1., 1., 1., 0.90062, 0.0993805, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. };

	std::vector<fun<float>> f1 = generatePyramidFunctionLevels(v1, 0);
	std::vector<fun<float>> f2 = generatePyramidFunctionLevels(v2, 0);


	std::vector<float> v0 = { 0.0f, 0.0f, 0.0f, 0.0f };
	float p0 = 15;
	int e_threshold = 0;
	float threshold = 0.001;

	auto lambda = [](float v1, float v2) -> bool {
		return true;
	};

	v0 = pyr_flow_1d_v0(lambda,
		listV0, p0, f1, f2, e_threshold, threshold);

	//displayFlowPoint(p0, v0, f1[0], f2[0], 0, (int)v1.size());

	EXPECT_TRUE(true);
}

TEST(cyclopeanOpticalFlow, cyclopeanOpticalFlowRow1) {
	int size = 10;

	float minNumber = 0.0;
	float maxNumber = 2.0;

	Matrix2D<float> listV0;
	listV0.reserve(size);

	listV0 = uniformDistribution2D(size, minNumber, maxNumber, true);

	std::vector<float> v1 = { 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.0993805, 0.90062, 1., 1., 1.,
		1., 1., 1., 0.90062, 0.0993805, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. };
	std::vector<float> v2 = { 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.0993805, 0.90062, 1., 1., 1.,
		1., 1., 1., 0.90062, 0.0993805, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. };

	std::vector<fun<float>> f1 = generatePyramidFunctionLevels(v1, 0);
	std::vector<fun<float>> f2 = generatePyramidFunctionLevels(v2, 0);

	Matrix2D<float> vRow;
	int e_threshold = 0;
	float threshold = 0.001;

	auto lambda = [](float v1, float v2) -> bool {
		return true;
	};

	vRow = cyclopeanOpticalFlowRow(lambda, listV0, f1, f2, e_threshold, threshold, 0.0f, (float)v1.size());

	displayFlowLine(vRow, f1[0], f2[0], 0.0f, (float)v1.size());
	

	EXPECT_TRUE(true);
}