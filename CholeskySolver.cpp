#include "LinearSystem.hpp"
#include "CholeskySolver.hpp"
#include <cmath>

CholeskySolver::CholeskySolver(const Matrix& A, const Vector& b): LinearSystem(A,b)
{
	SolverName = "Cholesky";
}

//Direct solver - Cholesky
Vector CholeskySolver::Solve()
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
