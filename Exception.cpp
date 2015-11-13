#include <iostream>
#include "Exception.hpp"
using namespace std;

Exception::Exception(std::string tagString, std::string problemString)
{
	mTag = tagString;
	mProblem = problemString;
}

void Exception::PrintDebug() const
{
	cerr << "Error (" << mTag << ")" << endl;
	cerr << "Problem: " << mProblem << endl;
}
