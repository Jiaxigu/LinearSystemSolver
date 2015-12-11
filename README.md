## Project description
This is a package of linear system solvers, developed by Jiaxi Gu for MATH-458 project.

## Package content  
- `lib/` includes `googletest-release-1.7.0`
- `CMakeLists.txt` must be in each subdirectory of the project  
- `main.cpp` driver file for main program, and the UI
- `Test_RunAll.cpp` driver file for google test suite
- 8 solver classes (LU, Cholesky, Jacobi, Gauss-Seidel, CG, PCG, Richardson, Thomas)
- 3 test classes (Vector, Matrix, LinearSystem)

## Tutorial
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

## How to import linear system from file
The file should be composed like:

A11 A12 ... A1n

A21 ... ... A2n

... ... ... ...

An1 An2 ... Ann

B1  B2  ... Bn

in which Ax = B.

Elements are divided by tab or space.
Source file should be in the root directory.

## Thanks to
[This case](https://github.com/dmonopoly/gtest-cmake-example) really helps a lot in implementing CMake + google test.
