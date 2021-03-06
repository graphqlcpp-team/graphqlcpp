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
#include "../../include/graphqlcpp/exceptions/InvalidRequestException.h"

using namespace std;
using namespace facebook::graphql;
using namespace facebook::graphql::ast;
using namespace graphqlcpp::validators;
using namespace graphqlcpp::exceptions;

#include <stdio.h>  /* defines FILENAME_MAX */
#include <chrono>

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
	const char * query = "subscription{user(id:1) {name: hallo}}";
	std::unique_ptr<Node> queryAst;
	queryAst = parseString(query, &error);
	ASSERT_TRUE(query);
	ASSERT_FALSE(error);

    error = nullptr;
    const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: ID!): User} type User { id: ID! name: string!	age: Int}";
    std::unique_ptr<Node> schemaAst;
    schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
    ASSERT_TRUE(schemaAst);
    ASSERT_FALSE(error);

    SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());
    QueryValidator* qv = new QueryValidator(saw);

	//bool operation = qv->isQueryValid(queryAst.get());
	ASSERT_THROW(qv->isQueryValid(queryAst.get()), WrongOperationException);
}

TEST(QueryValidatorTests, IsQueryValidWithValidQueryExpectNoError) {
    const char * error = nullptr;
    const char * query = "query{user(id:10) {name}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    error = nullptr;
    const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: ID!): User} type User { id: ID! name: string!	age: Int}";
    std::unique_ptr<Node> schemaAst;
    schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
    ASSERT_TRUE(schemaAst);
    ASSERT_FALSE(error);

    SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());
    QueryValidator* qv = new QueryValidator(saw);

	ASSERT_NO_THROW(qv->isQueryValid(queryAst.get()));
	Node* nodeQueryAst = queryAst.get();
	cout << "Checking if Query is valid at: ";
	auto start = std::chrono::system_clock::now();
	qv->isQueryValid(nodeQueryAst);
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end-start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::cout << "finished computation at " << std::ctime(&end_time)
			  << "elapsed time: " << elapsed_seconds.count() << "s\n";
}

TEST(QueryValidatorTests, IsQueryValidWithNotValidQueryExpectError) {
	const char * error = nullptr;
	const char * query = "query{age(id:1) {name}}";
	std::unique_ptr<Node> queryAst;
	queryAst = parseString(query, &error);
	ASSERT_TRUE(query);
	ASSERT_FALSE(error);

	error = nullptr;
	const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: ID!): User} type User { id: ID! name: string!	age: Int}";
	std::unique_ptr<Node> schemaAst;
	schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
	ASSERT_TRUE(schemaAst);
	ASSERT_FALSE(error);

	SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());
	QueryValidator* qv = new QueryValidator(saw);

	ASSERT_THROW(qv->isQueryValid(queryAst.get()), InvalidRequestException);
}

TEST(QueryValidatorTests, IsArgumentTypeBoolValidExpectNoError) {
    const char * error = nullptr;
    const char * query = "query{user(id:true) {name}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    error = nullptr;
    const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: Boolean!): User} type User { id: Boolean! name: string!	age: Int}";
    std::unique_ptr<Node> schemaAst;
    schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
    ASSERT_TRUE(schemaAst);
    ASSERT_FALSE(error);

    SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());
    QueryValidator* qv = new QueryValidator(saw);

    ASSERT_NO_THROW(qv->isQueryValid(queryAst.get()));
}

TEST(QueryValidatorTests, IsArgumentTypeIntValidExpectNoError) {
    const char * error = nullptr;
    const char * query = "query{user(id:100) {name}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    error = nullptr;
    const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: Int): User} type User { id: Int name: string!	age: Int}";
    std::unique_ptr<Node> schemaAst;
    schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
    ASSERT_TRUE(schemaAst);
    ASSERT_FALSE(error);

    SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());
    QueryValidator* qv = new QueryValidator(saw);

    ASSERT_NO_THROW(qv->isQueryValid(queryAst.get()));
}

TEST(QueryValidatorTests, IsArgumentTypeMultibleArgumentsValidExpectNoError) {
    const char * error = nullptr;
    const char * query = "query{user(id:100 name:x age: 5) {name}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    error = nullptr;
    const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: Int name: String! age: Int): User} type User { id: Int name: string!	age: Int}";
    std::unique_ptr<Node> schemaAst;
    schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
    ASSERT_TRUE(schemaAst);
    ASSERT_FALSE(error);

    SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());
    QueryValidator* qv = new QueryValidator(saw);

    ASSERT_NO_THROW(qv->isQueryValid(queryAst.get()));
}

TEST(QueryValidatorTests, IsArgumentTypeFloatValidExpectNoError) {
    const char * error = nullptr;
    const char * query = "query{user(id:100.07) {name}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    error = nullptr;
    const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: Float!): User} type User { id: Float! name: string!	age: Int}";
    std::unique_ptr<Node> schemaAst;
    schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
    ASSERT_TRUE(schemaAst);
    ASSERT_FALSE(error);

    SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());
    QueryValidator* qv = new QueryValidator(saw);

    ASSERT_NO_THROW(qv->isQueryValid(queryAst.get()));
}

TEST(QueryValidatorTests, IsArgumentTypeStringValidExpectNoError) {
    const char * error = nullptr;
    const char * query = "query{user(id:test) {name}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    error = nullptr;
    const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: String!): User} type User { id: String! name: string!	age: Int}";
    std::unique_ptr<Node> schemaAst;
    schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
    ASSERT_TRUE(schemaAst);
    ASSERT_FALSE(error);

    SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());
    QueryValidator* qv = new QueryValidator(saw);

    ASSERT_NO_THROW(qv->isQueryValid(queryAst.get()));
}

TEST(QueryValidatorTests, IsArgumentTypeBooleanValidExpectError) {
    const char * error = nullptr;
    const char * query = "query{user(id:la) {name}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    error = nullptr;
    const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: Boolean!): User} type User { id: Boolean! name: string!	age: Int}";
    std::unique_ptr<Node> schemaAst;
    schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
    ASSERT_TRUE(schemaAst);
    ASSERT_FALSE(error);
    SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());
    QueryValidator* qv = new QueryValidator(saw);

    ASSERT_THROW(qv->isQueryValid(queryAst.get()), InvalidRequestException);
}

TEST(QueryValidatorTests, IsArgumentValidExpectErrorBecauseNonNullType) {
    const char * error = nullptr;
    const char * query = "query{user {name}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    error = nullptr;
    const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: Boolean!): User} type User { id: Boolean! name: string!	age: Int}";
    std::unique_ptr<Node> schemaAst;
    schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
    ASSERT_TRUE(schemaAst);
    ASSERT_FALSE(error);
    SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());
    QueryValidator* qv = new QueryValidator(saw);

    ASSERT_THROW(qv->isQueryValid(queryAst.get()), InvalidRequestException);
}

TEST(QueryValidatorTests, IsArgumentValidExpectErrorBecauseWrongArgumentName) {
    const char * error = nullptr;
    const char * query = "query{user(la: 1) {name}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    error = nullptr;
    const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: Boolean!): User} type User { id: Boolean! name: string!	age: Int}";
    std::unique_ptr<Node> schemaAst;
    schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
    ASSERT_TRUE(schemaAst);
    ASSERT_FALSE(error);
    SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());
    QueryValidator* qv = new QueryValidator(saw);

    ASSERT_THROW(qv->isQueryValid(queryAst.get()), InvalidRequestException);
}

TEST(QueryValidatorTests, IsArgumentValidExpectNoErrorTwoArguments) {
    const char * error = nullptr;
    const char * query = "query{user(id: 10 name: Amelie) {name}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    error = nullptr;
    const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: Int!, name: String!): User} type User { id: Int! name: string!	age: Int}";
    std::unique_ptr<Node> schemaAst;
    schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
    ASSERT_TRUE(schemaAst);
    ASSERT_FALSE(error);
    SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());
    QueryValidator* qv = new QueryValidator(saw);

    ASSERT_NO_THROW(qv->isQueryValid(queryAst.get()));
}

TEST(QueryValidatorTests, IsArgumentValidExpectNoErrorThreeArgumentsButOnlyTwoRequired) {
    const char * error = nullptr;
    const char * query = "query{user(id: 10 name: Amelie) {name}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    error = nullptr;
    const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: Int! name: String! age: Int): User} type User { id: Int! name: string!	age: Int}";
    std::unique_ptr<Node> schemaAst;
    schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
    ASSERT_TRUE(schemaAst);
    ASSERT_FALSE(error);
    SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());
    QueryValidator* qv = new QueryValidator(saw);

    ASSERT_NO_THROW(qv->isQueryValid(queryAst.get()));
}

TEST(QueryValidatorTests, IsArgumentValidExpectNoErrorThreeAndThreeRequired) {
    const char * error = nullptr;
    const char * query = "query{user(id: 10 name: Amelie age: 22) {name}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    error = nullptr;
    const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: Int! name: String! age: Int!): User} type User { id: Int! name: string!	age: Int}";
    std::unique_ptr<Node> schemaAst;
    schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
    ASSERT_TRUE(schemaAst);
    ASSERT_FALSE(error);
    SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());
    QueryValidator* qv = new QueryValidator(saw);

    ASSERT_NO_THROW(qv->isQueryValid(queryAst.get()));
}

TEST(QueryValidatorTests, IsArgumentValidExpectErrorThreeAndThreeRequiredButOnlyTwo) {
    const char * error = nullptr;
    const char * query = "query{user(id: 10 age: 22) {name}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    error = nullptr;
    const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: Int! name: String! age: Int!): User} type User { id: Int! name: string!	age: Int}";
    std::unique_ptr<Node> schemaAst;
    schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
    ASSERT_TRUE(schemaAst);
    ASSERT_FALSE(error);
    SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());
    QueryValidator* qv = new QueryValidator(saw);

    ASSERT_THROW(qv->isQueryValid(queryAst.get()), InvalidRequestException);
}

TEST(QueryValidatorTests, IsArgumentValidExpectNoErrorThreeAndTwoRequiredDiffrentOrder) {
    const char * error = nullptr;
    const char * query = "query{user(age: 22 id: 10 ) {name}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    error = nullptr;
    const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: Int! name: String age: Int!): User} type User { id: Int! name: string age: Int}";
    std::unique_ptr<Node> schemaAst;
    schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
    ASSERT_TRUE(schemaAst);
    ASSERT_FALSE(error);
    SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());
    QueryValidator* qv = new QueryValidator(saw);

    ASSERT_NO_THROW(qv->isQueryValid(queryAst.get()));
}


TEST(QueryValidatorTests, IsArgumentValidExpectErrorThreeAndTwoRequiredOneWrongType) {
    const char * error = nullptr;
    const char * query = "query{user(id: 10 age: wuhu) {name}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    error = nullptr;
    const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: Int! name: String age: Int!): User} type User { id: Int! name: string age: Int}";
    std::unique_ptr<Node> schemaAst;
    schemaAst = parseStringWithExperimentalSchemaSupport(schema, &error);
    ASSERT_TRUE(schemaAst);
    ASSERT_FALSE(error);
    SchemaAstWraper* saw = new SchemaAstWraper(schemaAst.get());
    QueryValidator* qv = new QueryValidator(saw);

    ASSERT_THROW(qv->isQueryValid(queryAst.get()), InvalidRequestException);
}