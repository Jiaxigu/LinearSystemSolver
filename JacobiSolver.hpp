#ifndef JACOBISOLVERHEADERDEF
#define JACOBISOLVERHEADERDEF
#include "LinearSystem.hpp"

class JacobiSolver: public LinearSystem
{
public:
	JacobiSolver(const Matrix& A, const Vector& b);
	Vector Solve();
};

#endif
