/*
 * SchemaAstWrapperTest.cpp
 *
 *  Created on: 20.02.2019
 *      Author: Peter
 */


#include"gtest/gtest.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "../../include/graphqlparser/Ast.h"
#include "../../src/graphqlparser/GraphQLParser.h"
#include "../../src/graphqlparser/c/GraphQLAstToJSON.h"
#include "../../include/graphqlcpp/RequestAstWrapper.h"
#include "../../include/graphqlcpp/exceptions/WrongOperationException.h"
#include "../../include/graphqlcpp/exceptions/InvalidQueryException.h"


using namespace std;
using namespace facebook::graphql;
using namespace facebook::graphql::ast;
using namespace graphqlcpp;
using namespace graphqlcpp::exceptions;

#include <stdio.h>  /* defines FILENAME_MAX */


TEST(RequestAstWrapperTest, IsOperationValid) {
    const char *error = nullptr;
    const char *query = "query{user(id:1) {name: hallo}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    Node *node = queryAst.get();
    RequestAstWrapper *raw = new RequestAstWrapper(node);
    std::string operation = raw->extractOperation();
    ASSERT_TRUE(operation == "query");
}


