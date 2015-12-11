#include "LinearSystem.hpp"
#include "PCGSolver.hpp"
#include <cassert>
#include <iostream>
#include <cmath>

PCGSolver::PCGSolver(const Matrix& A, const Vector& b): LinearSystem(A,b)
{
	SolverName = "Preconditioned Conjugate Gradient";
}

//Iterative solver - Preconditioned Conjugate Gradient
Vector PCGSolver::Solve()
{
	int max;
	double tol;
	std::cout << "Input maximum number of iterations\n";
	std::cin >> max;
	assert (max > 0);
	std::cout << "Input tolerance\n";
	std::cin >> tol;
	assert (tol > 0.0);

	Matrix rA = *mpA;
	Vector rb = *mpb;
	Matrix iM(mSize, mSize);
	int ind;

	std::cout << "Please select your preferred preconditioner:\n";
	std::cout << "1 - Jacobi Preconditioner\n";
	std::cout << "2 - Incomplete Cholesky factorization\n";
	std::cin >> ind;
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
