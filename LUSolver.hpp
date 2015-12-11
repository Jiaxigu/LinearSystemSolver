#ifndef LUSOLVERHEADERDEF
#define LUSOLVERHEADERDEF
#include "LinearSystem.hpp"

class LUSolver: public LinearSystem
{
public:
	LUSolver(const Matrix& mA, const Vector& mb);
	Vector Solve();
};

#endif
