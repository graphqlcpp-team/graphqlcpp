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
#include <iostream>
#include "../../include/graphqlparser/Ast.h"
#include "../../src/graphqlparser/GraphQLParser.h"
#include "../../src/graphqlparser/c/GraphQLAstToJSON.h"
#include "../../include/graphqlcpp/validators/QueryValidator.h"
#include "../../include/graphqlcpp/validators/SchemaAstWraper.h"
#include "../../include/graphqlcpp/exceptions/WrongOperationException.h"
#include "../../include/graphqlcpp/exceptions/InvalidQueryException.h"


using namespace std;
using namespace facebook::graphql;
using namespace facebook::graphql::ast;
using namespace graphqlcpp::validators;
using namespace graphqlcpp::exceptions;

#include <stdio.h>  /* defines FILENAME_MAX */


TEST(SchemaAstWrapperTest, IsOperationValid) {
    const char *error = nullptr;
    const char *schema = "schema {query: Query, mutation: Mutation} type Query { user(id: ID!): User} type User { id: ID! name: string!	age: Int}";
    std::unique_ptr<Node> schemaAst;
    schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
    ASSERT_TRUE(schemaAst);
    ASSERT_FALSE(error);

    SchemaAstWraper *saw = new SchemaAstWraper(schemaAst.get());
    ASSERT_TRUE(saw->isOperationValid("mutation"));
}


