#ifndef CONJUGATEGRADIENTSOLVERHEADERDEF
#define CONJUGATEGRADIENTSOLVERHEADERDEF
#include "LinearSystem.hpp"

class ConjugateGradientSolver: public LinearSystem
{
public:
	ConjugateGradientSolver(const Matrix& mA, const Vector& mb);
	Vector Solve();
};

#endif
