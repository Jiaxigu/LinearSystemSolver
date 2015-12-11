#include "LinearSystem.hpp"
#include "JacobiSolver.hpp"
#include <cassert>
#include <iostream>

JacobiSolver::JacobiSolver(const Matrix& A, const Vector& b): LinearSystem(A,b)
{
	SolverName = "Jacobi";
}

//Iterative solver - Jacobi Convergence: diagonally dominant
Vector JacobiSolver::Solve()
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
