#ifndef LINEARSYSTEMHEADERDEF
#define LINEARSYSTEMHEADERDEF
#include "Vector.hpp"
#include "Matrix.hpp"
#include <string>

class LinearSystem
{
protected:
	int mSize;
	std::string SolverName;
	Matrix* mpA;
	Vector* mpb;

public:
	LinearSystem(const Matrix& A, const Vector& b);
	virtual ~LinearSystem();
	int GetSize() const;
	std::string GetName() const;
	virtual Vector Solve() = 0;
};

#endif
