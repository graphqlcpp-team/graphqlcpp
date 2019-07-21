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


TEST(GraphqlApiTest, setSchema) {
    GraphqlCppApi *api = ApiFactory::createApi();
    string schema = "query{user(id:1) {name}}";
    api->setGraphiQlIntrospectionSchema(schema);
    string res = api->getGraphiQlIntrospectionSchema();
    ASSERT_EQ(schema, res);
    delete api;
}

void checkIfStrEqu(const string &expected, const string &actual){
    char expCstr[expected.size() + 1];
    strcpy(expCstr, expected.c_str());

    char actCstr[actual.size() + 1];
    strcpy(actCstr, actual.c_str());

    ASSERT_STREQ(expCstr, actCstr);
}

TEST(GraphqlApiTest, integrationTestForLibraryGraphqlcpp){

    const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: ID!): User} type User { id: ID! name: string!	age: Int}";

    const char * query = "query{user(id:1) {name}}";
    GraphqlCppApi *api = ApiFactory::createApi();
    api->setSchema(schema);
    api->registerResolver(new GraphQlResolverTestData::UserResolver());
    string response = (api->executeRequest(query));
    string expected = R"({"data":{"name":"Herbert"}})";
    checkIfStrEqu(expected, response);
}

TEST(GraphqlApiTest, multipleChildesAtRootLevel){

    const char* schema = "schema {query: Query, mutation: Mutation} type Query { allUsers: [User]} type User { id: ID! name: string!	age: Int}";

    const char * query = "query{ allUsers {name}}";
    GraphqlCppApi *api = ApiFactory::createApi();
    api->setSchema(schema);
    auto resolver = new GraphQlResolverTestData::AllUserResolver();
    api->registerResolver(resolver);
    string response = (api->executeRequest(query));
    string expected = R"({"data":[{"name":"Herbert"},{"name":"Herbert"},{"name":"Herbert"}]})";
    checkIfStrEqu(expected, response);
}

//TODO test schreiben, ob nested listen typen also nicht auf root ebene auch funktionieren