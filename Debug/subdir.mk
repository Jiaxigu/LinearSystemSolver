################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CholeskySolver.cpp \
../ConjugateGradientSolver.cpp \
../Exception.cpp \
../GaussSeidelSolver.cpp \
../JacobiSolver.cpp \
../LUSolver.cpp \
../LinearSystem.cpp \
../Matrix.cpp \
../PCGSolver.cpp \
../RichardsonSolver.cpp \
../ThomasSolver.cpp \
../Vector.cpp \
../main.cpp 

OBJS += \
./CholeskySolver.o \
./ConjugateGradientSolver.o \
./Exception.o \
./GaussSeidelSolver.o \
./JacobiSolver.o \
./LUSolver.o \
./LinearSystem.o \
./Matrix.o \
./PCGSolver.o \
./RichardsonSolver.o \
./ThomasSolver.o \
./Vector.o \
./main.o 

CPP_DEPS += \
./CholeskySolver.d \
./ConjugateGradientSolver.d \
./Exception.d \
./GaussSeidelSolver.d \
./JacobiSolver.d \
./LUSolver.d \
./LinearSystem.d \
./Matrix.d \
./PCGSolver.d \
./RichardsonSolver.d \
./ThomasSolver.d \
./Vector.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


