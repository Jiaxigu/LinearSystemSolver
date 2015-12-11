#include "LinearSystem.hpp"
#include "ConjugateGradientSolver.hpp"
#include <cassert>
#include <iostream>

ConjugateGradientSolver::ConjugateGradientSolver(const Matrix& A, const Vector& b): LinearSystem(A,b)
{
	SolverName = "Conjugate Gradient";
}

//Iterative solver - Conjugate Gradient
Vector ConjugateGradientSolver::Solve()
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
