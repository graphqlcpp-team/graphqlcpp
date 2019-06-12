include_directories(validators)
include_directories(dispatcher)
include_directories(resolver)
include_directories(utils)

set(SOURCE_FILES
        GraphqlCppApi.cpp
        validators/QueryValidator.cpp
        validators/SchemaAstWraper.cpp
        validators/SchemaValidator.cpp
        dispatcher/RequestDispatcher.cpp
        ApiFactory.cpp
        RequestAstWrapper.cpp
        utils/MySerializer.cpp
        utils/MyWriter.cpp
        resolver/ResolverArgument.cpp
        resolver/IGraphQlResolver.cpp
        resolver/ResolverManager.cpp
        resolver/ResolverInfo.cpp
        utils/MySerializerChild.cpp
        utils/MySerializerRoot.cpp
        ../../include/graphqlcpp/GraphqlCppApi.h
        ../../include/graphqlcpp/validators/QueryValidator.h
        ../../include/graphqlcpp/validators/SchemaAstWraper.h
        ../../include/graphqlcpp/validators/SchemaValidator.h
        ../../include/graphqlcpp/dispatcher/RequestDispatcher.h
        ../../include/graphqlcpp/ApiFactory.h
        ../../include/graphqlcpp/RequestAstWrapper.h
        ../../include/graphqlcpp/utils/MySerializer.h
        ../../include/graphqlcpp/utils/MyWriter.h
        ../../include/graphqlcpp/resolver/ResolverArgument.h
        ../../include/graphqlcpp/resolver/IGraphQlResolver.h
        ../../include/graphqlcpp/resolver/ResolverManager.h
        ../../include/graphqlcpp/resolver/ResolverInfo.h
        ../../include/graphqlcpp/GraphQlDTOMultiRoot.h
        ../../include/graphqlcpp/GraphQlDTOSingleRoot.h
        ../../include/graphqlcpp/utils/MySerializerRoot.h
        ../../include/graphqlcpp/utils/MySerializerChild.h
        )


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
