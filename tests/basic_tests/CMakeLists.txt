enable_testing()
add_executable(runTests test_all.cpp ResolverManagerTest.cpp GraphQlResolverTestData.cpp
        RequestAstWrapperTest.cpp GraphqlCppApiTest.cpp DtoAndSerializerTest.cpp
        JsonVisitorTests.cpp JulianTests.cpp
        QueryValidatorTests.cpp
        SchemaAstWrapperTest.cpp
        TestData.cpp)


target_link_libraries(runTests graphqlcpp)
target_link_libraries(runTests gtest gtest_main)
add_subdirectory(data)