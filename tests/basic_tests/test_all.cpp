#include <iostream>
using namespace std;
#include "gtest/gtest.h"
//#include "QueryValidatorTests.cpp"


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  //falls man nur bestimmte Tests ausfuehren will:
  //::testing::GTEST_FLAG(filter) = "SchemaAst*";
  return RUN_ALL_TESTS();
}

