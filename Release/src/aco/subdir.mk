################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/aco/ACO.cpp \
../src/aco/Ant.cpp 

OBJS += \
./src/aco/ACO.o \
./src/aco/Ant.o 

CPP_DEPS += \
./src/aco/ACO.d \
./src/aco/Ant.d 


# Each subdirectory must supply rules for building sources it contributes
src/aco/%.o: ../src/aco/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


