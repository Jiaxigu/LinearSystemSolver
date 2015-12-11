#ifndef RICHARDSONSOLVERHEADERDEF
#define RICHARDSONSOLVERHEADERDEF
#include "LinearSystem.hpp"

class RichardsonSolver: public LinearSystem
{
public:
	RichardsonSolver(const Matrix& mA, const Vector& mb);
	Vector Solve();
};

#endif
