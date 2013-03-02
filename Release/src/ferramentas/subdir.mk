################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ferramentas/Conversor.cpp 

OBJS += \
./src/ferramentas/Conversor.o 

CPP_DEPS += \
./src/ferramentas/Conversor.d 


# Each subdirectory must supply rules for building sources it contributes
src/ferramentas/%.o: ../src/ferramentas/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


