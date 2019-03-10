include_directories(libgraphqlparser)
include_directories(libgraphqlparser/c)
include_directories(libgraphqlcpp)
include_directories(libgraphqlcpp/exceptions)
include_directories(libgraphqlcpp/validators)

set(SOURCE_FILES libgraphqlparser/c/GraphQLAst.cpp
        libgraphqlparser/c/GraphQLAst.h
        libgraphqlparser/c/GraphQLAstForEachConcreteType.h
        libgraphqlparser/c/GraphQLAstNode.cpp
        libgraphqlparser/c/GraphQLAstNode.h
        libgraphqlparser/c/GraphQLAstToJSON.cpp
        libgraphqlparser/c/GraphQLAstToJSON.h
        libgraphqlparser/c/GraphQLAstVisitor.cpp
        libgraphqlparser/c/GraphQLAstVisitor.h
        libgraphqlparser/c/GraphQLParser.cpp
        libgraphqlparser/c/GraphQLParser.h
        libgraphqlparser/Ast.cpp
        libgraphqlparser/Ast.h
        libgraphqlparser/AstNode.h
        libgraphqlparser/AstVisitor.h
        libgraphqlparser/dump_json_ast.cpp
        libgraphqlparser/GraphQLParser.cpp
        libgraphqlparser/GraphQLParser.h
        libgraphqlparser/JsonVisitor.cpp
        libgraphqlparser/JsonVisitor.h
        libgraphqlparser/lexer.cpp
        libgraphqlparser/lexer.h
        libgraphqlparser/location.hh
        libgraphqlparser/parser.tab.cpp
        libgraphqlparser/parser.tab.hpp
        libgraphqlparser/position.hh
        libgraphqlparser/stack.hh
        libgraphqlparser/syntaxdefs.h
        libgraphqlcpp/GraphqlCppApi.cpp
        libgraphqlcpp/GraphqlCppApi.h
        libgraphqlcpp/exceptions/InvalidSchemaException.h
        libgraphqlcpp/exceptions/NoSchemaSetException.h
        libgraphqlcpp/validators/QueryValidator.cpp
        libgraphqlcpp/validators/QueryValidator.h
        libgraphqlcpp/validators/SchemaAstWraper.cpp
        libgraphqlcpp/validators/SchemaAstWraper.h
        libgraphqlcpp/validators/SchemaValidator.cpp
        libgraphqlcpp/validators/SchemaValidator.h
        libgraphqlcpp/ApiFactory.cpp
        libgraphqlcpp/ApiFactory.h)

add_library(graphqlcpplib STATIC ${SOURCE_FILES})

target_include_directories(graphqlcpplib PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>)

install(TARGETS graphqlcpplib
        INCLUDES DESTINATION include
        ARCHIVE DESTINATION lib)