cmake_minimum_required(VERSION 3.10)
project(graphqlcpp     LANGUAGES CXX
        VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src/graphqlparser)
add_subdirectory(src/graphqlcpp)
add_subdirectory(tests)
