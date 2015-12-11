#include "gtest/gtest.h"
#include "Vector.hpp"
#include <cmath>

static int SIZE = 5;

class VectorTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		Vector test_init(SIZE);
		Vector test_sample(SIZE);
		for (int i=0; i<SIZE; i++)
		{
			test_sample[i] = i;
		}
	}

	Vector test_init;
	Vector test_sample;
};

TEST_F(VectorTest, IsInitSizeCorrect) {
	EXPECT_EQ(SIZE, test_init.GetSize());
}

TEST_F(VectorTest, IsInitValueZero) {
	for (int i=0; i<SIZE; i++) {
		EXPECT_EQ(0.0, test_init[i]);
	}
}

TEST_F(VectorTest, GetSizeWorks) {
	int TestSize = 10;
	Vector test_1(TestSize);
	EXPECT_EQ(TestSize, test_init.GetSize());
}

TEST_F(VectorTest, ReadWorks) {
	for (int i=0; i<SIZE; i++) {
		EXPECT_EQ(i, test_sample[i]);
	}
}

TEST_F(VectorTest, AssignmentWorks) {
	Vector test_assign(SIZE);
	test_assign = test_sample;
	for (int i=0; i<SIZE; i++) {
		EXPECT_EQ(i, test_assign[i]);
	}
	EXPECT_EQ(SIZE, test_assign.GetSize());
}

TEST_F(VectorTest, AdditionWorks) {
	Vector test_addition(SIZE);
	test_addition = test_sample + test_sample;
	for (int i=0; i<SIZE; i++) {
		EXPECT_EQ(2*i, test_addition[i]);
	}
	EXPECT_EQ(SIZE, test_addition.GetSize());
}

TEST_F(VectorTest, SubtractionWorks) {
	Vector test_subtraction(SIZE);
	test_subtraction = test_sample - test_sample;
	for (int i=0; i<SIZE; i++) {
		EXPECT_EQ(0.0, test_subtraction[i]);
	}
	EXPECT_EQ(SIZE, test_subtraction.GetSize());
}

TEST_F(VectorTest, MultiplyNumberWorks) {
	Vector test_multiply(SIZE);
	double factor = 5.0;
	test_multiply = test_sample * factor;
	for (int i=0; i<SIZE; i++) {
		EXPECT_EQ(factor * i, test_multiply[i]);
	}
	EXPECT_EQ(SIZE, test_multiply.GetSize());
}

TEST_F(VectorTest, MultiplyVectorWorks) {
	double product;
	double expected_product = 55.0;
	product = test_sample * test_sample;
	EXPECT_EQ(expected_product, product);
}

TEST_F(VectorTest, CalculateNormWorks) {
	double normp_2 = test_sample.CalculateNorm();
	double normp_1 = test_sample.CalculateNorm(1);
	double expected_normp_2 = sqrt(55.0);
	double expected_normp_1 = 15;
	EXPECT_EQ(expected_normp_2, normp_2);
	EXPECT_EQ(expected_normp_1, normp_1);
}
