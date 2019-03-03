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
#include "../../src/libgraphqlparser/Ast.h"
#include "../../src/libgraphqlparser/GraphQLParser.h"
#include "../../src/libgraphqlparser/c/GraphQLAstToJSON.h"
#include "../../src/libgraphqlcpp/validators/QueryValidator.h"
#include "../../src/libgraphqlcpp/validators/SchemaAstWraper.h"
#include "../../src/libgraphqlcpp/exceptions/WrongOperationException.h"

using namespace std;
using namespace facebook::graphql;
using namespace facebook::graphql::ast;
using namespace graphqlcpp::validators;
using namespace graphqlcpp::exceptions;

#include <stdio.h>  /* defines FILENAME_MAX */







TEST(SchemaAstWrapperTest, IterateThroughSchemaAst) {
	FILE *schemaFile;
 	schemaFile = fopen("schema-test-user.graphql", "r");
	ASSERT_TRUE(schemaFile != NULL);
	const char *error = nullptr;
	std::unique_ptr<Node> schemaAst;
	schemaAst = parseFileWithExperimentalSchemaSupport(schemaFile, &error);

	ASSERT_TRUE(schemaAst);
	ASSERT_FALSE(error);
	fclose(schemaFile);


	error = nullptr;
	const char * query = "{user(id:1) {age name {tada}}}";
	std::unique_ptr<Node> queryAst;
	queryAst = parseString(query, &error);
	ASSERT_TRUE(query);
	ASSERT_FALSE(error);

	SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());



//	printf(saw->printSchemaAsJson());

//	saw->nodeExsitstsAsChildOf();
}
