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

TEST(QueryValidatorTests, RightOperationType) {

	const char * error = nullptr;
	const char * query = "{user(id:1) {age name {tada}}}";
	std::unique_ptr<Node> queryAst;
	queryAst = parseString(query, &error);
	ASSERT_TRUE(query);
	ASSERT_FALSE(error);

	SchemaAstWraper* saw = new SchemaAstWraper(queryAst.get());
	QueryValidator* qv = new QueryValidator(saw);
	const char* operation = qv->getOperation(queryAst.get());
	ASSERT_STREQ(operation, "query");
}

TEST(QueryValidatorTests, IsQueryValidThrowsExecptionWhenWrongOperation) {
	const char * error = nullptr;
	const char * query = "mutation{user(id:1) {name: hallo}}";
	std::unique_ptr<Node> queryAst;
	queryAst = parseString(query, &error);
	ASSERT_TRUE(query);
	ASSERT_FALSE(error);

	SchemaAstWraper* saw = new SchemaAstWraper(queryAst.get());
	QueryValidator* qv = new QueryValidator(saw);
	//bool operation = qv->isQueryValid(queryAst.get());
	ASSERT_THROW(qv->isQueryValid(queryAst.get()), WrongOperationException);
}
