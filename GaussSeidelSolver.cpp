#include "LinearSystem.hpp"
#include "GaussSeidelSolver.hpp"
#include <cassert>
#include <iostream>

GaussSeidelSolver::GaussSeidelSolver(const Matrix& A, const Vector& b): LinearSystem(A,b)
{
	SolverName = "Gauss-Seidel";
}

//Iterative solver - Gauss-Seidel Convergence: diagonally dominant or positive-definite
Vector GaussSeidelSolver::Solve()
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
