################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/libgraphqlparser/Ast.cpp \
../src/libgraphqlparser/GraphQLParser.cpp \
../src/libgraphqlparser/JsonVisitor.cpp \
../src/libgraphqlparser/dump_json_ast.cpp \
../src/libgraphqlparser/lexer.cpp \
../src/libgraphqlparser/parser.tab.cpp 

OBJS += \
./src/libgraphqlparser/Ast.o \
./src/libgraphqlparser/GraphQLParser.o \
./src/libgraphqlparser/JsonVisitor.o \
./src/libgraphqlparser/dump_json_ast.o \
./src/libgraphqlparser/lexer.o \
./src/libgraphqlparser/parser.tab.o 

CPP_DEPS += \
./src/libgraphqlparser/Ast.d \
./src/libgraphqlparser/GraphQLParser.d \
./src/libgraphqlparser/JsonVisitor.d \
./src/libgraphqlparser/dump_json_ast.d \
./src/libgraphqlparser/lexer.d \
./src/libgraphqlparser/parser.tab.d 


# Each subdirectory must supply rules for building sources it contributes
src/libgraphqlparser/%.o: ../src/libgraphqlparser/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


