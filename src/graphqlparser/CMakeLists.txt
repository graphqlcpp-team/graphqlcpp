include_directories(c)

set(SOURCE_LIBGRAPHQLPARSER
        c/GraphQLAst.cpp
        c/GraphQLAstNode.cpp
        c/GraphQLAstToJSON.cpp
        c/GraphQLAstVisitor.cpp
        c/GraphQLParser.cpp
        Ast.cpp
        GraphQLParser.cpp
        JsonVisitor.cpp
        lexer.cpp
        parser.tab.cpp
        dump_json_ast.cpp)


set(HEADER_FILES libgraphqlcpp/GraphqlCppApi.h
        libgraphqlcpp/exceptions/InvalidSchemaException.h
        libgraphqlcpp/exceptions/NoSchemaSetException.h
        libgraphqlcpp/validators/QueryValidator.h
        libgraphqlcpp/validators/SchemaAstWraper.h
        libgraphqlcpp/validators/SchemaValidator.h
        libgraphqlcpp/ApiFactory.h
        libgraphqlparser/c/GraphQLAst.h
        libgraphqlparser/c/GraphQLAstForEachConcreteType.h
        libgraphqlparser/c/GraphQLAstNode.h
        libgraphqlparser/c/GraphQLAstToJSON.h
        libgraphqlparser/c/GraphQLAstVisitor.h
        libgraphqlparser/c/GraphQLParser.h
        libgraphqlparser/Ast.h
        libgraphqlparser/AstNode.h
        libgraphqlparser/AstVisitor.h
        libgraphqlparser/GraphQLParser.h
        libgraphqlparser/JsonVisitor.h
        libgraphqlparser/lexer.h
        libgraphqlparser/location.hh
        libgraphqlparser/parser.tab.hpp
        libgraphqlparser/position.hh
        libgraphqlparser/stack.hh
        libgraphqlparser/syntaxdefs.h)

add_library(graphqlparser STATIC ${SOURCE_LIBGRAPHQLPARSER})

target_include_directories(graphqlparser
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

include(GNUInstallDirs)

install(TARGETS graphqlparser
        EXPORT graphqlparser-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${LIBLEGACY_INCLUDE_DIRS}
        )
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/graphqlparser
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )
