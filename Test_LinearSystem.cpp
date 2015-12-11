#include "gtest/gtest.h"
#include "Vector.hpp"
#include "Matrix.hpp"
#include "LinearSystem.hpp"
#include "LUSolver.hpp"
#include "CholeskySolver.hpp"
#include "JacobiSolver.hpp"
#include "GaussSeidelSolver.hpp"
#include "ConjugateGradientSolver.hpp"
#include "PCGSolver.hpp"
#include "RichardsonSolver.hpp"
#include "ThomasSolver.hpp"

static int SIZE = 3;
static std::string TEST_INSTANCE_NAME = "LU";

class LinearSystemTest : public ::testing::Test {
public:
	LinearSystemTest() : test_B(SIZE), test_A(SIZE, SIZE), test_x(SIZE) {}
protected:
	virtual void SetUp() {
		//test_sample init values
		test_B(1) = 10; 	test_B(2) = 5; 		test_B(3) = 4;
		test_A(1,1) = 4; 	test_A(1,2) = 2; 	test_A(1,3) = -2;
		test_A(2,1) = 2; 	test_A(2,2) = 2; 	test_A(2,3) = -3;
		test_A(3,1) = -2; 	test_A(3,2) = -3; 	test_A(3,3) = 14;
	}

	Vector test_B;
	Matrix test_A;
	Vector test_x;
};

TEST_F(LinearSystemTest, IsInitSizeCorrect) {
	LUSolver test_Instance(test_A, test_B);
	EXPECT_EQ(SIZE, test_Instance.GetSize());
}

TEST_F(LinearSystemTest, IsInitNameCorrect) {
	LUSolver test_Instance(test_A, test_B);
	EXPECT_EQ(TEST_INSTANCE_NAME, test_Instance.GetName());
}

TEST_F(LinearSystemTest, LUSolverWorks) {
	LUSolver test_LU(test_A, test_B);
	test_x = test_LU.Solve();
	EXPECT_DOUBLE_EQ(2.0, test_x[0]);
	EXPECT_DOUBLE_EQ(2.0, test_x[1]);
	EXPECT_DOUBLE_EQ(1.0, test_x[2]);
}

TEST_F(LinearSystemTest, CholeskySolverWorks) {
	CholeskySolver test_Cholesky(test_A,test_B);
	test_x = test_Cholesky.Solve();
	EXPECT_DOUBLE_EQ(2.0, test_x[0]);
	EXPECT_DOUBLE_EQ(2.0, test_x[1]);
	EXPECT_DOUBLE_EQ(1.0, test_x[2]);
}




