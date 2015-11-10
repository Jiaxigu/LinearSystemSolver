#include <cmath>
#include <iostream>
#include <cassert>
#include "Vector.hpp"
#include "Matrix.hpp"


//override copy constructor
Matrix::Matrix(const Matrix& m1)
{
	mRows = m1.mRows;
	mCols = m1.mCols;
	mData = new double* [mRows];
	for (int i=0; i<mRows; i++)
	{
		mData[i] = new double [mCols];
	}
	for (int i=0; i<mRows; i++)
	{
		for (int j=0; j<mCols; j++)
		{
			mData[i][j] = m1.mData[i][j];
		}
	}
}

//override constructor
Matrix::Matrix(int Rows, int Cols)
{
	assert(Rows > 0);
	assert(Cols > 0);
	mRows = Rows;
	mCols = Cols;
	mData = new double* [mRows];
	for (int i=0; i<mRows; i++)
	{
		mData[i] = new double [mCols];
	}
	for (int i=0; i<mRows; i++)
	{
		for (int j=0; j<mCols; j++)
		{
			mData[i][j] = 0.0;
		}
	}
}

//override destructor
Matrix::~Matrix()
{
	for (int i=0; i<mRows; i++)
	{
		delete[] mData[i];
	}
	delete[] mData;
}

//get number of row of a matrix
int Matrix::GetRows() const
{
	return mRows;
}

//get number of columns of a matrix
int Matrix::GetCols() const
{
	return mCols;
}

//override operator ()
double& Matrix::operator()(int i, int j)
{
	assert(i > 0);
	assert(i < mRows+1);
	assert(j > 0);
	assert(j < mCols+1);
	return mData[i-1][j-1];
}

//override operator =
Matrix& Matrix::operator=(const Matrix& m1)
{
	assert(mRows = m1.mRows);
	assert(mCols = m1.mCols);
	for (int i=0; i<mRows; i++)
	{
		for (int j=0; j<mCols; j++)
		{
			mData[i][j] = m1.mData[i][j];
		}
	}
	return *this;
}

//override unary +
Matrix Matrix::operator+() const
{
	Matrix m1(mRows, mCols);
	for (int i=0;i<mRows; i++)
	{
		for (int j=0; j<mCols; j++)
		{
			m1(i+1, j+1) = mData[i][j];
		}
	}
	return m1;
}

//override unary -
Matrix Matrix::operator-() const
{
	Matrix m1(mRows, mCols);
	for (int i=0; i<mRows; i++)
	{
		for (int j=0; j<mCols; j++)
		{
			m1(i+1, j+1) = -mData[i][j];
		}
	}
	return m1;
}

//override operator +
Matrix Matrix::operator+(const Matrix& m1) const
{
	assert(mRows == m1.mRows);
	assert(mCols == m1.mCols);
	Matrix mNew (mRows, mCols);
	for (int i=0; i<mRows; i++)
	{
		for (int j=0; j<mCols; j++)
		{
		mNew(i+1,j+1) = mData[i][j] + m1.mData[i][j];
		}
	}
	return mNew;
}

//override operator -
Matrix Matrix::operator-(const Matrix& m1) const
{
	assert(mRows == m1.mRows);
	assert(mCols == m1.mCols);
	Matrix mNew (mRows, mCols);
	for (int i=0; i<mRows; i++)
	{
		for (int j=0; j<mCols; j++)
		{
		mNew(i+1,j+1) = mData[i][j] - m1.mData[i][j];
		}
	}
	return mNew;
}

//override operator *
Matrix Matrix::operator*(double a) const
{
	Matrix mNew (mRows, mCols);
	for (int i=0; i<mRows; i++)
	{
		for (int j=0; j<mCols; j++)
		{
			mNew(i+1,j+1) = a * mData[i][j];
		}
	}
	return mNew;
}

Matrix Matrix::operator*(const Matrix& m1) const
{
	assert(mCols == m1.mRows);
	Matrix m(mRows, m1.mCols);
	for (int i=0; i<mRows; i++)
	{
		for (int j=0; j<m1.mCols; j++)
		{
			for (int k=0; k<mCols; k++)
			{
				m(i+1,j+1) += mData[i][k] * m1.mData[k][j];
			}
		}
	}
	return m;
}

//calculate determinant of a matrix
double Matrix::CalculateDeterminant() const
{
	assert(mRows == mCols);
	double det = 0.0;
	if (mRows == 1)
	{
		det = mData[0][0];
	}
	else
	{
		for(int t=0; t<mRows; t++)
		{
			Matrix mSub (mRows-1, mCols-1);
			for (int i=0; i<mRows-1; i++)
			{
				for (int j=0; j<t; j++)
				{
					mSub(i+1, j+1) = mData[i+1][j];
				}
				for (int j=t;j<mRows-1;j++)
				{
					mSub(i+1,j+1) = mData[i+1][j+1];
				}
			}
			double mSubDet = mSub.CalculateDeterminant();
			det += pow(-1.0, t) * mData[0][t] * mSubDet;
		}
	}
	return det;
}

//calculate determinant of the k-th leading minor of a matrix
double Matrix::CalculateLeadingMinorDeterminant(int k) const
{
	assert(k > 0);
	assert(k < mRows+1);
	assert(mRows == mCols);
	Matrix mLeadingMinor (k, k);
	for (int i=0; i<k; i++)
	{
		for (int j=0; j<k; j++)
		{
			mLeadingMinor(i+1,j+1) = mData[i][j];
		}
	}
	return mLeadingMinor.CalculateDeterminant();
}

//Assert symmetric then assert positive for all leading minor determinant
void Matrix::AssertPositiveDefinite() const
{
	assert(mRows == mCols);
	for (int i=1; i<mRows; i++)
	{
		for (int j=0; j<i; j++)
		{
			assert (mData[i][j] == mData[j][i]);
		}
	}
	for (int k=1; k<mRows; k++)
	{
		assert (CalculateLeadingMinorDeterminant(k) > 0.0);
	}
}

//friend function to calculate the product of a matrix and a vector
Vector operator*(const Matrix& m, const Vector& v)
{
	int vSize = v.GetSize();
	assert(m.GetCols() == vSize);
	vSize = m.GetRows();
	Vector vNew(vSize);
	for (int i=0;i<vSize; i++)
	{
		for (int j=0; j<vSize; j++)
		{
			vNew[i] += m.mData[i][j] * v.Read(j);
		}
	}
	return vNew;
}

//friend function to calculate the product of a vector and a matrix
Vector operator*(const Vector& v, const Matrix& m)
{
	int vSize = v.GetSize();
	assert(m.GetRows() == vSize);
	vSize = m.GetCols();
	Vector vNew(vSize);
	for (int i=0;i<vSize; i++)
	{
		for (int j=0; j<vSize; j++)
		{
			vNew[i] += v.Read(j) * m.mData[j][i];
		}
	}
	return vNew;
}


