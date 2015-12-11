#include "gtest/gtest.h"
#include "Vector.hpp"
#include "Matrix.hpp"
#include <cmath>

static int ROW = 3;
static int COL = 2;

class MatrixTest : public ::testing::Test {
public:
	MatrixTest() : test_init(ROW, COL), test_sample(ROW, COL) {}
protected:
	virtual void SetUp() {
		//test_sample init values
		test_sample(1,1) = 4;	test_sample(1,2) = 2;
		test_sample(2,1) = -2;	test_sample(2,2) = 2;
		test_sample(3,1) = 2;	test_sample(3,2) = -3;
	}

	Matrix test_init;
	Matrix test_sample;
};

TEST_F(MatrixTest, IsInitSizeCorrect) {
	EXPECT_EQ(ROW, test_init.GetRows());
	EXPECT_EQ(COL, test_init.GetCols());
}

TEST_F(MatrixTest, IsInitValueZero) {
	for (int i=1; i<ROW+1; i++) {
		for (int j=1; j<COL+1; j++) {
			EXPECT_EQ(0.0, test_init(i,j));
		}
	}
}

TEST_F(MatrixTest, GetRowsWorks) {
	int TestRow = 10;
	Matrix test_1(TestRow, 1);
	EXPECT_EQ(TestRow, test_1.GetRows());
}

TEST_F(MatrixTest, GetColsWorks) {
	int TestCol = 8;
	Matrix test_1(1, TestCol);
	EXPECT_EQ(TestCol, test_1.GetCols());
}

TEST_F(MatrixTest, AssignmentWorks) {
	Matrix test_assign = test_sample;
	for (int i=1; i<ROW+1; i++) {
		for (int j=1; j<COL+1; j++) {
			EXPECT_EQ(test_assign(i,j), test_sample(i,j));
		}
	}
	EXPECT_EQ(ROW, test_assign.GetRows());
	EXPECT_EQ(COL, test_assign.GetCols());
}

TEST_F(MatrixTest, AdditionWorks) {
	Matrix test_addition = test_sample + test_sample;
	for (int i=1; i<ROW+1; i++) {
		for (int j=1; j<COL+1; j++) {
			EXPECT_EQ(test_addition(i,j), test_sample(i,j) + test_sample(i,j));
		}
	}
	EXPECT_EQ(ROW, test_addition.GetRows());
	EXPECT_EQ(COL, test_addition.GetCols());
}

TEST_F(MatrixTest, SubtractionWorks) {
	Matrix test_subtraction = test_sample - test_sample;
	for (int i=1; i<ROW+1; i++) {
		for (int j=1; j<COL+1; j++) {
			EXPECT_EQ(0.0, test_subtraction(i,j));
		}
	}
	EXPECT_EQ(ROW, test_subtraction.GetRows());
	EXPECT_EQ(COL, test_subtraction.GetCols());
}

TEST_F(MatrixTest, MultiplyNumberWorks) {
	double factor = 5.0;
	Matrix test_multiply = test_sample * factor;
	for (int i=1; i<ROW+1; i++) {
		for (int j=1; j<COL+1; j++) {
			EXPECT_EQ(test_multiply(i,j), test_sample(i,j) * factor);
		}
	}
	EXPECT_EQ(ROW, test_multiply.GetRows());
	EXPECT_EQ(COL, test_multiply.GetCols());
}

TEST_F(MatrixTest, MultiplyMatrixWorks) {
	int factor_col = 1;
	Matrix test_factor(COL, factor_col);
	test_factor(1,1) = 1.0;
	test_factor(2,1) = 1.0;
	Matrix product = test_sample * test_factor;

	EXPECT_EQ(6.0, product(1,1));
	EXPECT_EQ(0.0, product(2,1));
	EXPECT_EQ(-1.0, product(3,1));
	EXPECT_EQ(ROW, product.GetRows());
	EXPECT_EQ(factor_col, product.GetCols());
}

TEST_F(MatrixTest, CalculateDeterminantWorks) {
	Matrix test_det(2,2);
	test_det(1,1) = 3;	test_det(1,2) = 2;
	test_det(2,1) = 1; 	test_det(2,2) = 1;

	EXPECT_EQ(1.0, test_det.CalculateDeterminant());
}

TEST_F(MatrixTest, MatrixMultVectorWorks) {
	Vector factor_1(ROW);
	Vector factor_2(COL);
	for (int i=0; i<ROW; i++) {
		factor_1[i] = 1.0;
	}
	for (int j=0; j<COL; j++) {
		factor_2[j] = 0.0;
	}

	Vector product_1 = factor_1 * test_sample;
	Vector product_2 = test_sample * factor_2;

	EXPECT_EQ(4.0, product_1.Read(0));
	EXPECT_EQ(1.0, product_1.Read(1));
	EXPECT_EQ(0.0, product_2.Read(0));
	EXPECT_EQ(0.0, product_2.Read(1));
	EXPECT_EQ(0.0, product_2.Read(2));
}
