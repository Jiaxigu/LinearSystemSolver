# Project description
This is a package of linear system solvers, developed by Jiaxi Gu for MATH-458 project.

# Package content  
-`lib/` includes googletest-release-1.7.0.  
-`CMakeLists.txt` must be in each subdirectory of the project  

Rest include:
-`main.cpp` driver file for main program, and the UI
-`Test_RunAll.cpp` driver file for google test suite
- 8 different solvers(LU, Cholesky, Jacobi, Gauss-Seidel, CG, PCG, Richardson, Thomas); each as a class
- 3 test classes(Vector, Matrix, LinearSystem)

# Tutorial
In the project root:

    mkdir build
    cd build
    cmake ..

Then, to build and run main program:

    make
    ./LinearSystemSolver

To build and run tests:

    cmake -Dtest=ON ..
    make
    ./runUnitTests