#include <cmath>
#include <iostream>
#include <cassert>
#include "LinearSystem.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"
using namespace std;

//override copy constructor
LinearSystem::LinearSystem(const Matrix& A, const Vector& b)
{
	//assert if in same dimension
	int lsSize = A.GetRows();
	assert(A.GetCols() == lsSize);
	assert(b.GetSize() == lsSize);
	assert(A.CalculateDeterminant() != 0.0);

	mSize = lsSize;
	mpA = new Matrix(A);
	mpb = new Vector(b);
}

//override destructor
LinearSystem::~LinearSystem()
{
	delete mpA;
	delete mpb;
}

//Get the size of linear system
int LinearSystem::GetSize() const
{
	return mSize;
}

//Direct solver - Gaussian elimination
Vector LinearSystem::GaussElimSolver()
{
	Vector m(mSize);
	Vector solution(mSize);
	Matrix rA = *mpA;
	Vector rb = *mpb;

	for (int k=0; k<mSize-1; k++){
		// check if pivot necessary
		double max = 0.0;
		int row = -1;
		for (int i=k; i<mSize; i++)
		{
			if (fabs(rA(i+1,k+1)) > max)
			{
				row = i;
			}
		}
		assert(row > 0);

		//when pivot necessary
		if (row!=k)
		{
			for (int i=0; i<mSize;i++)
			{
				double tmp = rA(k+1,i+1);
				rA(k+1,i+1) = rA(row+1,i+1);
				rA(row+1,i+1) = tmp;
			}
			double tmp = rb(k+1);
			rb(k+1) = rb(row+1);
			rb(row+1) = tmp;
		}

		//forward elimination
		for (int i=k+1; i<mSize; i++)
		{
			m(i+1) = rA(i+1,k+1) / rA(k+1,k+1);
			for (int j=k; j<mSize; j++)
			{
				rA(i+1,j+1) -= rA(k+1,j+1) * m(i+1);
			}
			rb(i+1) -= rb(k+1) * m(i+1);
		}
	}

	//backward elimination
	for (int i=mSize-1; i>-1; i--)
	{
		solution(i+1) = rb(i+1);
		for (int j=i+1; j<mSize; j++)
		{
			solution(i+1) -=rA(i+1,j+1) * solution(j+1);
		}
		solution(i+1) /= rA(i+1,i+1);
	}
	return solution;
}

//Direct solver - LU decomposition
Vector LinearSystem::LUSolver()
{
	Matrix rA = *mpA;
	Vector rb = *mpb;
	Matrix LU(mSize, mSize);
	Vector Y(mSize);
	Vector solution(mSize);
	double factor;

	//Assert all det Ak != 0 - Exist unique LU decompostion
	for (int i=1; i<mSize; i++)
	{
		assert(rA.CalculateLeadingMinorDeterminant(i) != 0.0);
	}

	//Get matrix LU (the compact format for L and U in which A=L*U)
	for (int k=1; k<mSize+1; k++)
	{
		for (int i=k; i<mSize+1; i++)
		{
			factor = 0.0;
			for (int j=1; j<k; j++)
			{
				factor += LU(k,j) * LU(j,i);
			}
			LU(k,i) = rA(k,i) - factor;
		}

		for (int i=k+1; i<mSize+1; i++)
		{
			factor = 0.0;
			for (int j=1; j<k; j++)
			{
				factor += LU(i,j) * LU(j,k);
			}
			LU(i,k) = (rA(i,k) - factor) / LU(k,k);
		}
	}

	//Solve L*Y=b
	for (int k=1; k<mSize+1; k++)
	{
		factor = 0.0;
		for (int j=1; j<k; j++)
		{
			factor += LU(k,j) * Y(j);
		}
		Y(k) = rb(k) - factor;
	}

	//Solve U*X=Y
	for (int k=mSize; k>0; k--)
	{
		factor = 0.0;
		for (int j=k+1; j<mSize+1; j++)
		{
			factor += LU(k,j) * solution(j);
		}
		solution(k) = (Y(k) - factor) / LU(k,k);
	}
	return solution;
}

//Direct solver - Cholesky
Vector LinearSystem::CholeskySolver()
{
	Matrix rA = *mpA;
	Vector rb = *mpb;
	Matrix CH(mSize, mSize);
	Vector Y(mSize);
	Vector solution(mSize);
	double factor;

	//Assert if A is positive-definite
	rA.AssertPositiveDefinite();

	//Get matrix CH (the compact format for L and LT in which A=L*LT)
	for (int j=1; j<mSize+1; j++)
	{
		for (int i=j; i<mSize+1; i++)
		{
			factor = 0.0;
			for (int k=1; k<j; k++)
			{
				factor += CH(i,k) * CH(j,k);
			}
			if (i==j)
			{
				CH(i,j) = sqrt(rA(j,j) - factor);
			}
			else {
				CH(i,j) = (rA(i,j) - factor) / CH(j,j);
			}
		}
	}

	//Solve L*Y = b
	for (int i=1; i<mSize+1; i++)
	{
		factor = 0.0;
		for (int k=1; k<i; k++)
		{
			factor += CH(i,k) * Y(k);
		}
		Y(i) = (rb(i) - factor) / CH(i,i);
	}

	//Solve LT*X=Y
	for (int i=mSize; i>0; i--)
	{
		factor = 0.0;
		for (int k=i+1; k<mSize+1; k++)
		{
			factor += CH(k,i) * solution(k);
		}
		solution(i) = (Y(i) - factor) / CH(i,i);
	}
	return solution;
}

//Direct solver - Thomas Algorithm (tridiagonal system in linear time)
Vector LinearSystem::ThomasSolver()
{
	Matrix rA = *mpA;
	Vector rb = *mpb;
	Vector solution(mSize);
	Vector c(mSize-1);
	Vector d(mSize);

	c(1) = rA(1,2) / rA(1,1);
	d(1) = rb(1) / rA(1,1);
	for (int i=2; i<mSize; i++)
	{
		c(i) = rA(i,i+1) / (rA(i,i) - rA(i,i-1) * c(i-1));
	}
	for (int i=2; i<mSize+1; i++)
	{
		d(i) = (rb(i) - rA(i,i-1) * d(i-1)) / (rA(i,i) - rA(i,i-1) * c(i-1));
	}

	solution(mSize) = d(mSize);
	for (int i=mSize-1; i>0; i--)
	{
		solution(i) = d(i) - c(i) * solution(i+1);
	}
	return solution;
}

//Iterative solver - Jacobi Convergence: diagonally dominant
Vector LinearSystem::JacobiSolver(int max, double tol)
{
	assert (tol > 0.0);
	assert (max > 0);
	Matrix rA = *mpA;
	Vector rb = *mpb;
	Vector xold(mSize);
	Vector xnew(mSize);
	Vector err(mSize);
	err = rA * xnew - rb;
	double factor;
	int k = 0;
	double res = err.CalculateNorm();

	//check nonsingular and diagonal entries are not zero
	assert (rA.CalculateDeterminant() != 0);
	for (int i=1; i<mSize+1; i++)
	{
		assert (rA(i,i) != 0.0);
	}

	//Jacobi iteration
	while ((k < max) && (res > tol))
	{
		xold = xnew;
		for (int i=1; i<mSize+1; i++)
		{
			factor = 0.0;
			for (int j=1; j<mSize+1; j++)
			{
				if(j!=i)
				{
					factor += rA(i,j) * xold(j);
				}
			}
			xnew(i) = (rb(i) - factor) / rA(i,i);
		}
		err = rA * xnew - rb;
		res = err.CalculateNorm();
		k++;
	}
	return xnew;
}

//Iterative solver - Gauss-Seidel Convergence: diagonally dominant or positive-definite
Vector LinearSystem::GaussSeidelSolver(int max, double tol)
{
	assert (tol > 0.0);
	assert (max > 0);
	Matrix rA = *mpA;
	Vector rb = *mpb;
	Vector solution(mSize);
	Vector err(mSize);
	err = rA * solution - rb;
	double factor;
	int k = 0;
	double res = err.CalculateNorm();

	//check nonsingular and diagonal entries are not zero
	assert (rA.CalculateDeterminant() != 0);
	for (int i=1; i<mSize+1; i++)
	{
		assert (rA(i,i) != 0.0);
	}

	//Gauss-Seidel Iteration
	while ((k < max) && (res > tol))
	{
		for (int i=1; i<mSize+1; i++)
		{
			factor = 0.0;
			for (int j=1; j<mSize+1; j++)
			{
				if(j!=i)
				{
					factor += rA(i,j) * solution(j);
				}
			}
			solution(i) = (rb(i) - factor) / rA(i,i);
		}
		err = rA * solution - rb;
		res = err.CalculateNorm();
		k++;
	}
	return solution;
}

//Iterative solver - Modified Richardson
Vector LinearSystem::RichardsonSolver(int max, double tol, double omega)
{
	assert (tol > 0.0);
	assert (max > 0);
	Matrix rA = *mpA;
	Vector rb = *mpb;
	Vector xold(mSize);
	Vector xnew(mSize);
	Vector R(mSize);
	int k = 0;
	double res = (rA * xnew - rb).CalculateNorm();

//	//Convergence
//	Matrix I(mSize, mSize);
//	Matrix err(mSize, mSize);
//	for (int i=1; i<mSize+1; i++)
//	{
//		I(i,i) = 1.0;
//	}
//	err = I - rA * omega;
//	double norm = 0.0;
//	for (int i=1; i<mSize+1; i++)
//	{
//		for (int j=1; j<mSize+1; j++)
//		{
//			norm += pow(err(i,j), 2.0);
//		}
//	}
//	norm = sqrt(norm);
//	assert(norm<1);

	//R(k) = b - A * x(k), x(k+1) = x(k) + omega * R(k)
	while ((k < max) && (res > tol))
	{
		xold = xnew;
		R = rb - rA * xold;
		xnew = xold + R * omega;
		res = (xnew-xold).CalculateNorm();
		k++;
	}
	return xnew;
}

//Iterative solver - Conjugate gradient
Vector LinearSystem::ConjugateGradientSolver(int max, double tol)
{
	assert (tol > 0.0);
	assert (max > 0);
	Matrix rA = *mpA;
	Vector rb = *mpb;
	Vector r = rb;
	Vector p = r;
	Vector solution(mSize);
	int k = 0;
	double dotR, alpha, beta;


//	//Convergence: Assert if A is positive-definite
//	rA.AssertPositiveDefinite();

	//Conjugate gradient iteration
	while ((k < max) && (r.CalculateNorm() > tol))
	{
		dotR = r * r;
		alpha = dotR / (p * rA * p);
		solution = solution + p * alpha;
		r = r - (rA * p * alpha);
		beta = r * r / dotR;
		p = r + p * beta;
		k++;
	}
	return solution;
}

Vector LinearSystem::PreconditionedConjugateGradientSolver(int max, double tol)
{
	assert (tol > 0.0);
	assert (max > 0);
	Matrix rA = *mpA;
	Vector rb = *mpb;
	Matrix iM(mSize, mSize);
	int ind;

	cout << "Please select your preferred preconditioner:\n";
	cout << "1 - Jacobi Preconditioner\n";
	cout << "2 - Incomplete Cholesky factorization\n";
	cin >> ind;
	assert ((ind == 1) || (ind == 2));
	if (ind == 1)
	{
		for (int i=1; i<mSize+1; i++)
		{
			iM(i,i) = 1.0 / rA(i,i);
		}
	}
	else if (ind == 2)
	{
		Matrix L(mSize,mSize);
		Matrix LT(mSize,mSize);
		double factor;
		for (int i=1; i<mSize+1; i++)
		{
			factor = 0.0;
			for (int k=1; k<i-1; k++)
			{
				factor += L(i,k) * L(i,k);
			}
			L(i,i) = sqrt((rA(i,i) - factor));
			LT(i,i) = L(i,i);
			for (int j=i+1; j<mSize; j++)
			{
				factor = 0.0;
				for (int k=1; k<i-1; k++)
				{
					factor += L(i,k) * L(j,k);
				}
				L(j,i) = (rA(i,j) - factor) / L(i,i);
				LT(i,j) = L(j,i);
			}
		}
		iM  = L * LT;
	}

	Vector r = rb;
	Vector z = iM * r;
	Vector p = z;
	Vector solution(mSize);
	int k = 0;
	double dotRZ, alpha, beta;

	while (((k < max) && (r.CalculateNorm() > tol)))
	{
		dotRZ = r * z;
		alpha = dotRZ / (p * rA * p);
		solution = solution + p * alpha;
		r = r - rA * p * alpha;
		z = iM * r;
		beta = r * z / dotRZ;
		p = z + p * beta;
		k++;
	}
	return solution;
}

