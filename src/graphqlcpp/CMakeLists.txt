include_directories(validators)

set(SOURCE_FILES
        GraphqlCppApi.cpp
        validators/QueryValidator.cpp
        validators/SchemaAstWraper.cpp
        validators/SchemaValidator.cpp
        ApiFactory.cpp utils/MySerializer.cpp utils/MyWriter.cpp resolver/ResolverArgument.cpp ../../include/graphqlcpp/resolver/ResolverArgument.h resolver/IGraphQlResolver.cpp ../../include/graphqlcpp/resolver/IGraphQlResolver.h)


add_library(graphqlcpp STATIC ${SOURCE_FILES})


target_link_libraries(graphqlcpp graphqlparser)

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
