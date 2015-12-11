#include "Vector.hpp"
#include "Matrix.hpp"
#include "LinearSystem.hpp"
#include "LUSolver.hpp"
#include "CholeskySolver.hpp"
#include "JacobiSolver.hpp"
#include "GaussSeidelSolver.hpp"
#include "ConjugateGradientSolver.hpp"
#include "PCGSolver.hpp"
#include "RichardsonSolver.hpp"
#include "ThomasSolver.hpp"
#include "Exception.hpp"
#include <iostream>
#include <cassert>
#include <fstream>
using namespace std;

void StartSolver();
int MainMenu();
int SolverMenu();
int FileOutputMenu();
void SolverSelect(Matrix A, Vector B);
void LinearSystemDemo();
void LinearSystemInputFromCommandLine();
void LinearSystemInputFromFile();
void LinearSystemOutputToFile(Vector solution);

int main (int argc, char* argv[])
{
	static int VERSION = 3;
	cout << "////////////////////\n";
	cout << "Linear System Solver\n";
	cout << "For MATH-458 Project\n";
	cout << "////////////////////\n";
	cout << "Author  -   " << "Jiaxi Gu\n";
	cout << "Version -   " << VERSION << "\n";
	cout << "Date    -   " << "10/12/2015\n";

	StartSolver();

	cout << "Exit successful\n";
	return 0;
}

void StartSolver()
{
	int index;
	index = MainMenu();

	switch(index)
	{
		case 1:
			LinearSystemDemo();
			StartSolver();
			break;
		case 2:
			LinearSystemInputFromCommandLine();
			StartSolver();
			break;
		case 3:
			LinearSystemInputFromFile();
			StartSolver();
			break;
		default:
			break;
	}
}

int MainMenu()
{
	int index;
	cout << "Menu:\n";
	cout << "1 - See Demo\n";
	cout << "2 - Input in command line\n";
	cout << "3 - Input from file\n";
	cout << "4 - Exit\n";

	while ( !(cin >> index) || ((index != 1) && (index != 2) && (index != 3) && (index != 4)))
	{
		cout << "Bad input - try again\n";
		cin.clear();
		cin.get();
	}

	return index;
}

int SolverMenu()
{
	int index;
	cout << "Please select solver:\n";
	cout << "1 - LU\n";
	cout << "2 - Cholesky\n";
	cout << "3 - Jacobi\n";
	cout << "4 - Gauss-Seidel\n";
	cout << "5 - Richardson\n";
	cout << "6 - Conjugate Gradient\n";
	cout << "7 - Preconditioned Conjugate Gradient\n";
	cout << "8 - Thomas Tridiagonal Algorithm\n";
	cout << "0 - Return to main menu\n";

	while ( !(cin >> index) ||
			((index != 1) && (index != 2) && (index != 3) &&
			 (index != 4) && (index != 5) && (index != 6) &&
			 (index != 7) && (index != 8) && (index != 0)))
	{
		cout << "Bad input - try again\n";
		cin.clear();
		cin.get();
	}
	return index;
}

int FileOutputMenu()
{
	int index;
	cout << "Output to file?\n";
	cout << "1 - Yes\n";
	cout << "2 - No\n";

	while ( !(cin >> index) || ((index != 1) && (index != 2)))
	{
		cout << "Bad input - try again\n";
		cin.clear();
		cin.get();
	}
	return index;
}

void SolverSelect(Matrix A, Vector B)
{
	int SIZE = B.GetSize();
	Vector x(SIZE);

	int index = SolverMenu();

	cout << std::showpos;
	cout.precision(5);
	cout.setf(std::ios::fixed, std::ios::floatfield);

	if (index == 1)
	{
		LUSolver LS(A,B);
		x = LS.Solve();
		cout << LS.GetName() << endl;
	}
	else if (index == 2)
	{
		CholeskySolver LS(A,B);
		x = LS.Solve();
		cout << LS.GetName() << endl;
	}
	else if (index == 3)
	{
		JacobiSolver LS(A,B);
		x = LS.Solve();
		cout << LS.GetName() << endl;
	}
	else if (index == 4)
	{
		GaussSeidelSolver LS(A,B);
		x = LS.Solve();
		cout << LS.GetName() << endl;
	}
	else if (index == 5)
	{
		RichardsonSolver LS(A,B);
		x = LS.Solve();
		cout << LS.GetName() << endl;
	}
	else if (index == 6)
	{
		ConjugateGradientSolver LS(A,B);
		x = LS.Solve();
		cout << LS.GetName() << endl;
	}

	else if (index == 7)
	{
		PCGSolver LS(A,B);
		x = LS.Solve();
		cout << LS.GetName() << endl;

	}
	else if (index == 8)
	{
		ThomasSolver LS(A,B);
		x = LS.Solve();
		cout << LS.GetName() << endl;
	}

	if (index != 0)
	{
		cout << x;
		LinearSystemOutputToFile(x);
		SolverSelect(A,B);
	}


}

void LinearSystemDemo ()
{
	//Demo for linear system solver
	int SIZE = 3;
	Vector B(SIZE);
	Matrix A(SIZE,SIZE);
	Vector x(SIZE);

	cout << std::showpos;
	cout.precision(5);
	cout.setf(std::ios::fixed, std::ios::floatfield);

	cout << "///////////////////////\n";
	cout << "Demo for direct methods\n";
	cout << "///////////////////////\n";

	//1 - Positive-definite matrix demo set
	B(1) = 10; 		B(2) = 5; 		B(3) = 4;
	A(1,1) = 4; 	A(1,2) = 2; 	A(1,3) = -2;
	A(2,1) = 2; 	A(2,2) = 2; 	A(2,3) = -3;
	A(3,1) = -2; 	A(3,2) = -3; 	A(3,3) = 14;
	cout << "\n1 - Positive-definite demo set\n";

	//LU
	LUSolver LU(A,B);
	cout << LU.GetName() << endl;
	cout << LU.Solve() << endl;

	//Cholesky
	CholeskySolver Cholesky(A,B);
	cout << Cholesky.GetName() << endl;
	cout << Cholesky.Solve() << endl;
}

void LinearSystemInputFromCommandLine ()
{
	int SIZE;
	cout << "Size of the linear system (number of rows):\n";
	while (!(cin >> SIZE) || (SIZE < 0))
	{
		cout << "Bad input - try again\n";
		cin.clear();
		cin.get();
	}
	Vector B(SIZE);
	Matrix A(SIZE,SIZE);

	cout << std::noshowpos;

	for (int i=1; i<SIZE+1; i++)
	{
		for (int j=1; j<SIZE+1; j++)
		{
			cout << "Input element in A: Row " << i << ", Column " << j <<"\n";
			cin >> A(i,j);
		}
	}
	for (int i=1; i<SIZE+1; i++)
	{
		cout << "Input " << i << "th element in b\n";
		cin >> B(i);
	}

	SolverSelect(A,B);
}

void LinearSystemInputFromFile()
{
	int SIZE;
	bool ERROR_FLAG = false;
	cout << "Size of the linear system (number of rows):\n";
	while (!(cin >> SIZE) || (SIZE < 0))
	{
		cout << "Bad input - try again\n";
		cin.clear();
		cin.get();
	}
	Vector B(SIZE);
	Matrix A(SIZE,SIZE);
	try
	{
		char filename[50];
		cout << "Please type the name of the input file:\n";
		cin >> filename;
		ifstream read_file(filename);
		if(read_file.is_open() == false)
		{
			throw (Exception("FILE", "Can not read file"));
		}
		while(!read_file.eof())
		{
			for (int i=1; i<SIZE+1; i++)
			{
				for (int j=1; j<SIZE+1; j++)
				{
					read_file >> A(i,j);
				}
			}
			for (int i=1; i<SIZE+1; i++)
			{
				read_file >> B(i);
			}
		}
		read_file.close();
	}
	catch (Exception& error)
	{
		ERROR_FLAG = true;
		error.PrintDebug();
		LinearSystemInputFromFile();
	}
	if(!ERROR_FLAG)
	{
		SolverSelect(A,B);
	}
}

void LinearSystemOutputToFile(Vector solution)
{
	int OutputIndex = FileOutputMenu();
	if (OutputIndex == 1)
	{

		try
		{
			char filename[50];
			cout << "Please type the name of the input file:\n";
			cin >> filename;
			ofstream write_output(filename, ios::app);
			if(write_output.is_open() == false)
			{
				throw (Exception("FILE", "Can not write to file"));
			}
			write_output.setf(ios::scientific);
			write_output.precision(5);
			write_output << solution;
			write_output.close();
		}

		catch (Exception& error)
		{
			error.PrintDebug();
			LinearSystemOutputToFile(solution);
		}
	}
}
