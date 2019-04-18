enable_testing()
add_executable(runTests test_all.cpp RequestDispatcherTest.cpp RequestAstWrapperTest.cpp GraphqlCppApiTest.cpp DtoAndSerializerTest.cpp JsonVisitorTests.cpp JulianTests.cpp ParserTests.cpp QueryValidatorTests.cpp SchemaAstWrapperTest.cpp TestData.cpp)


target_link_libraries(runTests graphqlcpp)
target_link_libraries(runTests gtest gtest_main)
add_subdirectory(data)