#include "LinearSystem.hpp"
#include "RichardsonSolver.hpp"
#include <cassert>
#include <iostream>

RichardsonSolver::RichardsonSolver(const Matrix& A, const Vector& b): LinearSystem(A,b)
{
	SolverName = "Richardson";
}

//Iterative solver - Modified Richardson
Vector RichardsonSolver::Solve()
{
	int max;
	double tol;
	double omega;
	std::cout << "Input maximum number of iterations\n";
	std::cin >> max;
	assert ( max > 0);
	std::cout << "Input tolerance\n";
	std::cin >> tol;
	assert (tol > 0.0);
	std::cout << "Input omega\n";
	std::cin >> omega;
	assert (omega > 0.0);

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



