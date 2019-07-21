#include <iostream>
using namespace std;
#include "gtest/gtest.h"

/***
 * Run all Tests
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
//falls man nur bestimmte Tests ausfuehren will:
//::testing::GTEST_FLAG(filter) = "SchemaAst*";

