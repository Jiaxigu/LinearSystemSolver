#ifndef PCGSOLVERHEADERDEF
#define PCGSOLVERHEADERDEF
#include "LinearSystem.hpp"

class PCGSolver: public LinearSystem
{
public:
	PCGSolver(const Matrix& mA, const Vector& mb);
	Vector Solve();
};

#endif
