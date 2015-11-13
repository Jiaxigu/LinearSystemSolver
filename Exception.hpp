/*
 * Name:	Exception.hpp
 * Created:	13nd November, 2015
 * Author:	Jiaxi Gu
 *
 * Part of MATH-458 project
 * All rights reserved
 */

#ifndef EXCEPTIONDEF
#define EXCEPTIONDEF

#include <string>

class Exception
{
private:
	std::string mTag, mProblem;
public:
	Exception(std::string tagString, std::string problemString);
	void PrintDebug() const;
};

#endif
