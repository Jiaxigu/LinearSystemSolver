#ifndef VECTORHEADERDEF
#define VECTORHEADERDEF
#include <iostream>

class Vector
{
private:
	double* mData;
	int mSize;
public:
	Vector(const Vector& v1);
	Vector(int size);
	~Vector();
	int GetSize() const;
	double& operator[](int i);
	double Read(int i) const;
	double& operator() (int i);
	Vector& operator=(const Vector& v1);
	Vector operator+() const;
	Vector operator-() const;
	Vector operator+(const Vector& v1) const;
	Vector operator-(const Vector& v1) const;
	Vector operator*(double a) const;
	double operator*(const Vector& v1) const;
	double CalculateNorm(int p=2) const;
	friend std::ostream& operator<<(std::ostream& output, const Vector& z);
};

std::ostream& operator<<(std::ostream& output, const Vector& z);

#endif
