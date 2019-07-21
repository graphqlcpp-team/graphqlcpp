#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "../../include/graphqlcpp/GraphqlCppApi.h"
#include "GraphQlResolverTestData.cpp"
#include"gtest/gtest.h"

using namespace std;
using namespace facebook::graphql;
using namespace facebook::graphql::ast;
using namespace graphqlcpp::api;


TEST(IntegrationTest, createAndDelete){
    string schema = "schema {query: Query, mutation: Mutation} type Query { user(id: ID!): User} type User { id: ID! name: string!	age: Int}";
    GraphqlCppApi *api = GraphqlCppApi::createInstance();
    api->setSchema(schema);
    delete api;
    string schema2 = "schema {query: Query } type Query { car: Car} type Car { wheels: [Wheel]} type Wheel {pressure:Int}";
    GraphqlCppApi *api2 = GraphqlCppApi::createInstance();
    api2->setSchema(schema2);
    delete api2;
}

TEST(IntegrationTest, singleChildTest){

    string schema = "schema {query: Query, mutation: Mutation} type Query { user(id: ID!): User} type User { id: ID! name: string!	age: Int}";

    string query = "query{user(id:1) {name}}";
    GraphqlCppApi *api = GraphqlCppApi::createInstance();
    api->setSchema(schema);
    api->registerResolver(new GraphQlResolverTestData::UserResolver());
    string response = (api->executeRequest(query));
    string expected = R"({"data":{"name":"Herbert"}})";
    ASSERT_EQ(expected, response);
    delete api;
}

TEST(IntegrationTest, multipleChildesAtRootLevel){

    string schema = "schema {query: Query, mutation: Mutation} type Query { allUsers: [User]} type User { id: ID! name: string!	age: Int}";

    string query = "query{ allUsers {name}}";
    GraphqlCppApi *api = GraphqlCppApi::createInstance();
    api->setSchema(schema);
    auto resolver = new GraphQlResolverTestData::AllUserResolver();
    api->registerResolver(resolver);
    string response = (api->executeRequest(query));
    string expected = R"({"data":[{"name":"Herbert"},{"name":"Herbert"},{"name":"Herbert"}]})";
    ASSERT_EQ(expected, response);

    delete api;
}

TEST(IntegrationTest, multipleChildes){

    string schema = "schema {query: Query } type Query { car: Car} type Car { wheels: [Wheel]} type Wheel {pressure:Int}";

    string query = "query{ car { wheels { pressure } } }";
    GraphqlCppApi *api = GraphqlCppApi::createInstance();
    api->setSchema(schema);
    auto resolver = new GraphQlResolverTestData::CarResolver();
    api->registerResolver(resolver);
    string response = (api->executeRequest(query));
    string expected = R"({"data":{"wheels":[{"pressure":1},{"pressure":2},{"pressure":3},{"pressure":4}]}})";
    ASSERT_EQ(expected, response);

    delete api;
}

TEST(IntegrationTest, setSchemaTest) {
    GraphqlCppApi *api = GraphqlCppApi::createInstance();
    string schema = "query{user(id:1) {name}}";
    api->setGraphiQlIntrospectionSchema(schema);
    string res = api->getGraphiQlIntrospectionSchema();
    ASSERT_EQ(schema, res);
    delete api;
}