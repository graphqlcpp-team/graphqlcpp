################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/libgraphqlparser/c/GraphQLAst.cpp \
../src/libgraphqlparser/c/GraphQLAstNode.cpp \
../src/libgraphqlparser/c/GraphQLAstToJSON.cpp \
../src/libgraphqlparser/c/GraphQLAstVisitor.cpp \
../src/libgraphqlparser/c/GraphQLParser.cpp 

OBJS += \
./src/libgraphqlparser/c/GraphQLAst.o \
./src/libgraphqlparser/c/GraphQLAstNode.o \
./src/libgraphqlparser/c/GraphQLAstToJSON.o \
./src/libgraphqlparser/c/GraphQLAstVisitor.o \
./src/libgraphqlparser/c/GraphQLParser.o 

CPP_DEPS += \
./src/libgraphqlparser/c/GraphQLAst.d \
./src/libgraphqlparser/c/GraphQLAstNode.d \
./src/libgraphqlparser/c/GraphQLAstToJSON.d \
./src/libgraphqlparser/c/GraphQLAstVisitor.d \
./src/libgraphqlparser/c/GraphQLParser.d 


# Each subdirectory must supply rules for building sources it contributes
src/libgraphqlparser/c/%.o: ../src/libgraphqlparser/c/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


