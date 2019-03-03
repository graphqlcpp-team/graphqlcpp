enable_testing()
add_executable(runTests test_all.cpp GraphqlCppApiTest.cpp JsonVisitorTests.cpp JulianTests.cpp ParserTests.cpp QueryValidatorTests.cpp SchemaAstWrapperTest.cpp)


target_link_libraries(runTests graphqlcpp)
target_link_libraries(runTests gtest gtest_main)
