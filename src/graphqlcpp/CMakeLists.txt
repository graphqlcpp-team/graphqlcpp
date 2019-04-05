include_directories(validators)

set(SOURCE_FILES
        GraphqlCppApi.cpp
        validators/QueryValidator.cpp
        validators/SchemaAstWraper.cpp
        validators/SchemaValidator.cpp
        ApiFactory.cpp Serializer.cpp Serializer.h IGraphQlDTO.cpp IGraphQlDTO.h)


add_library(graphqlcpp STATIC ${SOURCE_FILES})


target_link_libraries(graphqlcpp graphqlparser)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})
target_link_libraries(graphqlcpp ${JSONCPP_LIBRARIES})

target_include_directories(graphqlcpp
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

include(GNUInstallDirs)

install(TARGETS graphqlcpp
        EXPORT graphqlcpp-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${LIBLEGACY_INCLUDE_DIRS}
        )
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/graphqlcpp
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )
