#include <iostream>
#include "Exception.hpp"
Exception::Exception(std::string tagString, std::string problemString)
{
	mTag = tagString;
	mProblem = problemString;
}

void Exception::PrintDebug() const
{
	std::cerr << "Error (" << mTag << ")" << std::endl;
	std::cerr << "Problem: " << mProblem << std::endl;
}
