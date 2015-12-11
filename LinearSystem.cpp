#include <cmath>
#include <iostream>
#include <cassert>
#include "LinearSystem.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"

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

std::string LinearSystem::GetName() const
{
	return SolverName;
}

