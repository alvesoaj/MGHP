################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/fuzzy/Fuzzy.cpp \
../src/fuzzy/FuzzyComposition.cpp \
../src/fuzzy/FuzzyIO.cpp \
../src/fuzzy/FuzzyInput.cpp \
../src/fuzzy/FuzzyOutput.cpp \
../src/fuzzy/FuzzyRule.cpp \
../src/fuzzy/FuzzyRuleAntecedent.cpp \
../src/fuzzy/FuzzyRuleConsequent.cpp \
../src/fuzzy/FuzzySet.cpp 

OBJS += \
./src/fuzzy/Fuzzy.o \
./src/fuzzy/FuzzyComposition.o \
./src/fuzzy/FuzzyIO.o \
./src/fuzzy/FuzzyInput.o \
./src/fuzzy/FuzzyOutput.o \
./src/fuzzy/FuzzyRule.o \
./src/fuzzy/FuzzyRuleAntecedent.o \
./src/fuzzy/FuzzyRuleConsequent.o \
./src/fuzzy/FuzzySet.o 

CPP_DEPS += \
./src/fuzzy/Fuzzy.d \
./src/fuzzy/FuzzyComposition.d \
./src/fuzzy/FuzzyIO.d \
./src/fuzzy/FuzzyInput.d \
./src/fuzzy/FuzzyOutput.d \
./src/fuzzy/FuzzyRule.d \
./src/fuzzy/FuzzyRuleAntecedent.d \
./src/fuzzy/FuzzyRuleConsequent.d \
./src/fuzzy/FuzzySet.d 


# Each subdirectory must supply rules for building sources it contributes
src/fuzzy/%.o: ../src/fuzzy/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


