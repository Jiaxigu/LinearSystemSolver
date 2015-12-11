#ifndef MATRIXHEADERDEF
#define MATRIXHEADERDEF
#include "Vector.hpp"

class Matrix
{
private:
	double** mData;
	int mRows, mCols;
public:
	Matrix(const Matrix& m1);
	Matrix(int mRows, int mCols);
	~Matrix();
	int GetRows() const;
	int GetCols() const;
	double& operator()(int i, int j);
	Matrix& operator=(const Matrix& m1);
	Matrix operator+() const;
	Matrix operator-() const;
	Matrix operator+(const Matrix& m1) const;
	Matrix operator-(const Matrix& m1) const;
	Matrix operator*(double a) const;
	Matrix operator*(const Matrix& m1) const;
	double CalculateDeterminant() const;
	double CalculateLeadingMinorDeterminant(int k) const;
	void AssertPositiveDefinite() const;
	friend Vector operator*(const Matrix& m, const Vector& v);
	friend Vector operator*(const Vector& v, const Matrix& m);
};

Vector operator*(const Matrix& m, const Vector& v);
Vector operator*(const Vector& v, const Matrix& m);

#endif
