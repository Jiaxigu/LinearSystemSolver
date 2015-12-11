#include "LinearSystem.hpp"
#include "ThomasSolver.hpp"

ThomasSolver::ThomasSolver(const Matrix& A, const Vector& b): LinearSystem(A,b)
{
	SolverName = "Thomas Tridiagonal Algorithm";
}

//Direct solver - Thomas Algorithm (tridiagonal system in linear time)
Vector ThomasSolver::Solve()
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
