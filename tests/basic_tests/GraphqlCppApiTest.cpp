#include"gtest/gtest.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../../include/graphqlcpp/GraphqlCppApi.h"
#include "../../include/graphqlcpp/ApiFactory.h"
#include <string>
#include "GraphQlResolverTestData.cpp"

using namespace std;
using namespace facebook::graphql;
using namespace facebook::graphql::ast;
using namespace graphqlcpp::api;

//TEST(GraphqlApiTest, dumpAstAsJson) {
//	const char * query = "query{user(id:1) {name}}";
//	const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: ID!): User} type User { id: ID! name: string!	age: Int}";
//
//	GraphqlCppApi* api = ApiFactory::createApi();
//	api->setSchema(schema);
//
//
//
//	string result = "";
//    result = api->executeRequest(query);
//
//	cout << result;
//
//	//ASSERT_NE(nullptr, result);
//}

TEST(GraphqlApiTest, setSchema) {
    GraphqlCppApi *api = ApiFactory::createApi();
    string schema = "query{user(id:1) {name}}";
    api->setGraphiQlIntrospectionSchema(schema);
    string res = api->getGraphiQlIntrospectionSchema();
    ASSERT_EQ(schema, res);
    delete api;
}

TEST(GraphqlApiTest, all){

    const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: ID!): User} type User { id: ID! name: string!	age: Int}";

    demo::User *user = demo::TestDataGenerator::createUser();

    const char * query = "query{user(id:1) {name}}";
    GraphqlCppApi *api = ApiFactory::createApi();
    api->setSchema(schema);
    api->registerResolver(new GraphQlResolverTestData::UserResolver());
    const char *response = (api->executeRequest(query)).c_str();
    const char *expected = "{\"data\":{\"name\":\"Herbert\"}}";
    ASSERT_STREQ(expected, response);
}

