include_directories(libgraphqlparser)
include_directories(libgraphqlparser/c)
include_directories(libgraphqlcpp)
include_directories(libgraphqlcpp/exceptions)
include_directories(libgraphqlcpp/validators)

set(SOURCE_LIBGRAPHQLPARSER libgraphqlparser/c/GraphQLAst.cpp
        libgraphqlparser/c/GraphQLAstNode.cpp
        libgraphqlparser/c/GraphQLAstToJSON.cpp
        libgraphqlparser/c/GraphQLAstVisitor.cpp
        libgraphqlparser/c/GraphQLParser.cpp
        libgraphqlparser/Ast.cpp
        libgraphqlparser/GraphQLParser.cpp
        libgraphqlparser/JsonVisitor.cpp
        libgraphqlparser/lexer.cpp
        libgraphqlparser/parser.tab.cpp
        libgraphqlparser/dump_json_ast.cpp
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

set(SOURCE_FILES
        libgraphqlcpp/GraphqlCppApi.cpp

        libgraphqlcpp/validators/QueryValidator.cpp
        libgraphqlcpp/validators/SchemaAstWraper.cpp
        libgraphqlcpp/validators/SchemaValidator.cpp
        libgraphqlcpp/ApiFactory.cpp
        )

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
        libgraphqlparser/syntaxdefs.h libgraphqlcpp/exceptions/ArgumentNotValidException.h)

add_library(graphqlcpplib STATIC ${SOURCE_FILES} ${HEADER_FILES} ${SOURCE_LIBGRAPHQLPARSER})

target_include_directories(graphqlcpplib PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>)

install(TARGETS graphqlcpplib
        ARCHIVE DESTINATION lib)
install(FILES ${HEADER_FILES} DESTINATION include)
