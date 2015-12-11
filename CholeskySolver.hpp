#ifndef CHOLESKYSOLVERHEADERDEF
#define CHOLESKYSOLVERHEADERDEF
#include "LinearSystem.hpp"

class CholeskySolver: public LinearSystem
{
public:
	CholeskySolver(const Matrix& mA, const Vector& mb);
	Vector Solve();
};

#endif
