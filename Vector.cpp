#include <cmath>
#include <iostream>
#include <cassert>
#include "Vector.hpp"
using namespace std;

//override copy constructor
Vector::Vector(const Vector& v1)
{
	mSize = v1.GetSize();
	mData = new double [mSize];
	for (int i=0; i<mSize; i++)
	{
		mData[i] = v1.mData[i];
	}
}

//override constructor
Vector::Vector(int size)
{
	assert(size > 0);
	mSize = size;
	mData = new double [mSize];
	for (int i=0; i<mSize; i++)
	{
		mData[i] = 0.0;
	}
}

//override destructor
Vector::~Vector()
{
	delete[] mData;
}

//get size of a vector
int Vector::GetSize() const
{
	return mSize;
}

//override operator []
double& Vector::operator[](int i)
{
	assert(i > -1);
	assert(i < mSize);
	return mData[i];
}

//read only version of []
double Vector::Read(int i) const
{
	assert(i > -1);
	assert(i < mSize);
	return mData[i];
}

//override operator ()
double& Vector::operator() (int i)
{
	assert(i > 0);
	assert(i < mSize+1);
	return mData[i-1];
}

//override operator =
Vector& Vector::operator=(const Vector& v1)
{
	assert(mSize == v1.mSize);
	for (int i=0; i<mSize; i++)
	{
		mData[i] = v1.mData[i];
	}
	return *this;
}

//override unary +
Vector Vector::operator+() const
{
	Vector v(mSize);
	for (int i=0; i<mSize; i++)
	{
		v[i] =  mData[i];
	}
	return v;
}

//override unary -
Vector Vector::operator-() const
{
	Vector v(mSize);
	for (int i=0; i<mSize; i++)
	{
		v[i] =  -mData[i];
	}
	return v;
}

//override operator +
Vector Vector::operator+(const Vector& v1) const
{
	assert (mSize == v1.mSize);
	Vector v(mSize);
	for (int i=0; i<mSize; i++)
	{
		v[i] = mData[i] + v1.mData[i];
	}
	return v;
}

//override operator -
Vector Vector::operator-(const Vector& v1) const
{
	assert (mSize == v1.mSize);
	Vector v(mSize);
	for (int i=0; i<mSize; i++)
	{
		v[i] = mData[i] - v1.mData[i];
	}
	return v;
}

//override operator * with a scalar
Vector Vector::operator*(double a) const
{
	Vector v(mSize);
	for (int i=0; i<mSize; i++)
	{
		v[i] = a * mData[i];
	}
	return v;
}

//override operator * with a vector
double Vector::operator*(const Vector& v1) const
{
	assert (mSize == v1.mSize);
	double product = 0.0;
	for (int i=0; i<mSize; i++)
	{
		product += mData[i] * v1.mData[i];
	}
	return product;
}

//calculate norm, with default value
double Vector::CalculateNorm(int p) const
{
	double val, sum = 0.0;
	for (int i=0; i<mSize; i++)
	{
		sum += pow(fabs(mData[i]), (double)(p));
	}
	val = pow(sum, 1.0/((double)(p)));
	return val;
}

std::ostream& operator<<(std::ostream& output, const Vector& z)
{
	cout << showpos;
	cout.precision(5);
	cout.setf(ios::fixed, ios::floatfield);

	for (int i=1; i<z.mSize+1; i++)
	{
		output << z.Read(i-1) << "\t";
	}
	output << endl;
	return output;
}
