/*
 * Name:	LinearSystem.hpp
 * Created:	22nd October, 2015
 * Author:	Jiaxi Gu
 *
 * Part of MATH-458 project
 * All rights reserved
 */

#ifndef LINEARSYSTEMHEADERDEF
#define LINEARSYSTEMHEADERDEF
#include "Vector.hpp"
#include "Matrix.hpp"

class LinearSystem
{
private:
	int mSize;
	Matrix* mpA;
	Vector* mpb;
	LinearSystem(const LinearSystem& ls1);

public:
	LinearSystem(const Matrix& A, const Vector& b);
	~LinearSystem();
	int GetSize() const;
	Vector GaussElimSolver();
	Vector LUSolver();
	Vector CholeskySolver();
	Vector ConjugateGradientSolver(int max, double tol);
	Vector JacobiSolver(int max, double tol);
	Vector GaussSeidelSolver(int max, double tol);
	Vector RichardsonSolver(int max, double tol, double omega);
//	Vector PreconditionedConjugateGradientSolver(int max, double tol);
};

#endif
