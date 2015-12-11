#ifndef GAUSSSEIDELSOLVERHEADERDEF
#define GAUSSSEIDELSOLVERHEADERDEF
#include "LinearSystem.hpp"

class GaussSeidelSolver: public LinearSystem
{
public:
	GaussSeidelSolver(const Matrix& mA, const Vector& mb);
	Vector Solve();
};

#endif
