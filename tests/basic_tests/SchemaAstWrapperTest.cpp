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
	const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: ID!): User} type User { id: ID! name: string!	age: Int}";
	std::unique_ptr<Node> schemaAst;
	schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
	ASSERT_TRUE(schemaAst);
	ASSERT_FALSE(error);

	SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());
	ASSERT_TRUE(saw->isOperationValid("mutation"));

}



TEST(SchemaAstWrapperTest, IterateThroughSchemaAst) {

	const char *error = nullptr;
	const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: ID!): User} "
					  "type User { id: ID! name: Name age: Int} type Name {vorname: String name: String}";
	std::unique_ptr<Node> schemaAst;
	schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
	ASSERT_TRUE(schemaAst);
	ASSERT_FALSE(error);
	//const char *jsonSchemaString = graphql_ast_to_json((const struct GraphQLAstNode *)ast.get());

	SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());
	ASSERT_TRUE(saw->nodeExistsAsChildOf("user", "query"));
	ASSERT_TRUE(saw->nodeExistsAsChildOf("name", "user"));
	ASSERT_TRUE(saw->nodeExistsAsChildOf("name", "name"));
	ASSERT_FALSE(saw->nodeExistsAsChildOf("name", "query"));
}

TEST(SchemaAstWrapperTest, CheckIfArgumentValid) {

    const char *error = nullptr;
    const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: ID!): User} "
                         "type User { id: ID! name: Name age: Int} type Name {vorname: String name: String}";
    std::unique_ptr<Node> schemaAst;
    schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
    ASSERT_TRUE(schemaAst);
    ASSERT_FALSE(error);
    //const char *jsonSchemaString = graphql_ast_to_json((const struct GraphQLAstNode *)ast.get());

    SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());
}
