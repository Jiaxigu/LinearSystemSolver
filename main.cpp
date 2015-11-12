#include <iostream>
#include <cassert>
#include <fstream>
#include "Vector.hpp"
#include "Matrix.hpp"
#include "LinearSystem.hpp"
using namespace std;

void StartSolver();
int MainMenu();
int SolverMenu();
int FileOutputMenu();
void SolverSelect(Matrix A, Vector B);
void LinearSystemDemo();
void LinearSystemInputFromCommandLine();
void LinearSystemInputFromFile();

int main (int argc, char* argv[])
{
	static int VERSION = 2;
	cout << "////////////////////\n";
	cout << "Linear System Solver\n";
	cout << "For MATH-458 Project\n";
	cout << "////////////////////\n";
	cout << "Author  -   " << "Jiaxi Gu\n";
	cout << "Version -   " << VERSION << "\n";
	cout << "Date    -   " << "12/11/2015\n";

	StartSolver();

	cout << "Exit successful";
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

	cin >> index;
	assert ((index == 1) || (index == 2) || (index == 3) || (index ==4));
	return index;
}

int SolverMenu()
{
	int index;
	cout << "Please select solver:\n";
	cout << "1 - Gauss Elimination\n";
	cout << "2 - LU\n";
	cout << "3 - Cholesky\n";
	cout << "4 - Thomas Tridiagonal Algorithm\n";
	cout << "5 - Jacobi\n";
	cout << "6 - Gauss-Seidel\n";
	cout << "7 - Richardson\n";
	cout << "8 - Conjugate Gradient\n";
	cout << "9 - Preconditioned Conjugate Gradient\n";
	cout << "0 - Return to main menu\n";

	cin >> index;
	assert ((index == 1) || (index == 2) || (index == 3) ||
			(index == 4) || (index == 5) || (index == 6) ||
			(index == 7) || (index == 8) || (index == 9) ||
			(index == 0));

	return index;
}

int FileOutputMenu()
{
	int index;
	cout << "Output to file?\n";
	cout << "1 - Yes\n";
	cout << "2 - No\n";

	cin >> index;
	assert ((index == 1) || (index == 2));
	return index;
}

void SolverSelect(Matrix A, Vector B)
{
	LinearSystem LS(A,B);
	int SIZE = LS.GetSize();
	Vector x(SIZE);
	int index = SolverMenu();

	cout << std::showpos;
	cout.precision(5);
	cout.setf(std::ios::fixed, std::ios::floatfield);

	if (index == 1)
	{
		x = LS.GaussElimSolver();
		cout << "Gauss Elimination\n";
	}
	else if (index == 2)
	{
		x = LS.LUSolver();
		cout << "LU\n";
	}
	else if (index == 3)
	{
		x = LS.CholeskySolver();
		cout << "Cholesky\n";
	}
	else if (index == 4)
	{
		x = LS.ThomasSolver();
		cout << "Thomas Tridiagonal Algorithm\n";
	}
	else if (index == 5)
	{
		int maxIter;
		double tol;
		cout << "Input maximum number of iterations\n";
		cin >> maxIter;
		assert ( maxIter > 0);
		cout << "Input tolerance\n";
		cin >> tol;
		assert (tol > 0);

		x = LS.JacobiSolver(maxIter, tol);
		cout << "Jacobi\n";
	}
	else if (index == 6)
	{
		int maxIter;
		double tol;
		cout << "Input maximum number of iterations\n";
		cin >> maxIter;
		assert ( maxIter > 0);
		cout << "Input tolerance\n";
		cin >> tol;
		assert (tol > 0);

		x = LS.GaussSeidelSolver(maxIter, tol);
		cout << "Gauss-Seidel\n";
	}

	else if (index == 7)
	{
		int maxIter;
		double tol;
		double omega;
		cout << "Input maximum number of iterations\n";
		cin >> maxIter;
		assert ( maxIter > 0);
		cout << "Input tolerance\n";
		cin >> tol;
		assert (tol > 0.0);
		cout << "Input omega\n";
		cin >> omega;
		assert (omega > 0.0);

		x = LS.RichardsonSolver(maxIter, tol, omega);
		cout << "Richardson\n";
	}
	else if (index == 8)
	{
		int maxIter;
		double tol;
		cout << "Input maximum number of iterations\n";
		cin >> maxIter;
		assert ( maxIter > 0);
		cout << "Input tolerance\n";
		cin >> tol;
		assert (tol > 0);

		x = LS.ConjugateGradientSolver(maxIter, tol);
		cout << "Conjugate Gradient\n";
	}
	else if (index == 9)
	{
		int maxIter;
		double tol;
		cout << "Input maximum number of iterations\n";
		cin >> maxIter;
		assert ( maxIter > 0);
		cout << "Input tolerance\n";
		cin >> tol;
		assert (tol > 0);

		x = LS.PreconditionedConjugateGradientSolver(maxIter, tol);
		cout << "Preconditioned Conjugate Gradient\n";
	}

	if (index != 0)
	{
		cout << x;
		int OutputIndex = FileOutputMenu();
		if (OutputIndex == 1)
		{
			ofstream write_output("Output.dat", ios::app);
			assert (write_output.is_open());
			write_output.setf(ios::scientific);
			write_output.precision(5);
			write_output << x;
			write_output.close();
		}
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

	cout << "////////////////////////////////\n";
	cout << "Demo for my linear system solver\n";
	cout << "////////////////////////////////\n";

	//1 - Positive-definite matrix demo set
	B(1) = 10; 		B(2) = 5; 		B(3) = 4;
	A(1,1) = 4; 	A(1,2) = 2; 	A(1,3) = -2;
	A(2,1) = 2; 	A(2,2) = 2; 	A(2,3) = -3;
	A(3,1) = -2; 	A(3,2) = -3; 	A(3,3) = 14;
	LinearSystem LSPD(A,B);
	cout << "\n1 - Positive-definite demo set\n";

	//Gauss Elimination
	x = LSPD.GaussElimSolver();
	std::cout << "Gauss Elimination\n";
	cout << x;

	//LU
	x = LSPD.LUSolver();
	cout << "LU\n";
	cout <<  x;

	//Cholesky
	x = LSPD.CholeskySolver();
	cout << "Cholesky\n";
	cout << x;

	//Conjugate Gradient
	x = LSPD.ConjugateGradientSolver(10, 0.000001);
	cout << "Conjugate Gradient\n";
	cout << x;

	//Gauss-Seidel
	x = LSPD.GaussSeidelSolver(15, 0.000001);
	cout << "Gauss-Seidel\n";
	cout << x;


	//2 - Diagonally dominant matrix test set
	B(1) = 3; 		B(2) = 15; 		B(3) = 10;
	A(1,1) = 10; 	A(1,2) = -2; 	A(1,3) = -1;
	A(2,1) = -2; 	A(2,2) = 10; 	A(2,3) = -1;
	A(3,1) = -1; 	A(3,2) = -2; 	A(3,3) = 5;
	LinearSystem LSJ(A,B);
	cout << "\n2 - Diagonally dominant test set\n";

	//Conjugate Gradient
	x = LSJ.ConjugateGradientSolver(10, 0.000001);
	cout << "Conjugate Gradient\n";
	cout << x;

	//Jacobi
	x = LSJ.JacobiSolver(15, 0.000001);
	cout << "Jacobi\n";
	cout << x;

	//Gauss-Seidel
	x = LSJ.GaussSeidelSolver(10, 0.000001);
	cout << "Gauss-Seidel\n";
	cout << x;

	//Richardson
	x = LSJ.RichardsonSolver(15, 0.000001, 0.1);
	cout << "Richardson\n";
	cout << x;

	cout << "\n";
}

void LinearSystemInputFromCommandLine ()
{
	int SIZE;
	cout << "Size of the linear system (number of rows):\n";
	cin >> SIZE;
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
	cout << "Size of the linear system (number of rows):\n";
	cin >> SIZE;
	Vector B(SIZE);
	Matrix A(SIZE,SIZE);

	char filename[50];
	cout << "Please type the name of the input file:\n";
	cin >> filename;

	ifstream read_file(filename);
	assert(read_file.is_open());
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
	SolverSelect(A,B);
}
