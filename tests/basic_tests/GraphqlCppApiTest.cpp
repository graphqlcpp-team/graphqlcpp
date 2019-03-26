#include"gtest/gtest.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../../include/graphqlcpp/GraphqlCppApi.h"
#include "../../include/graphqlcpp/ApiFactory.h"


using namespace std;
using namespace facebook::graphql;
using namespace facebook::graphql::ast;
using namespace graphqlcpp::api;

TEST(GraphQlApiTest, dumpAstAsJson){
	const char * query = "query{user(id:1) {name}}";

	const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: ID!): User} type User { id: ID! name: string!	age: Int}";
	//const char* simpleSchema = "{ me { name } }";

	GraphqlCppApi* api = ApiFactory::createApi();
	api->setSchema(schema);
	cout << api->executeQuery(query);
	//auto json = api->printSchemaAsJson();
	//cout << json;
	//ASSERT_NE(nullptr, json);

}

