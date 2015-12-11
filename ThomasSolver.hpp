#ifndef THOMASSOLVERHEADERDEF
#define THOMASSOLVERHEADERDEF
#include "LinearSystem.hpp"

class ThomasSolver: public LinearSystem
{
public:
	ThomasSolver(const Matrix& mA, const Vector& mb);
	Vector Solve();
};

#endif
