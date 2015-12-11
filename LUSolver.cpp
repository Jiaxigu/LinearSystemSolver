#include "LinearSystem.hpp"
#include "LUSolver.hpp"
#include <cassert>

LUSolver::LUSolver(const Matrix& A, const Vector& b): LinearSystem(A,b)
{
	SolverName = "LU";
}

//Direct solver - LU decomposition
Vector LUSolver::Solve()
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
