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


TEST(IntegrationTest, setSchema) {
    GraphqlCppApi *api = GraphqlCppApi::createInstance();
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

TEST(IntegrationTest, libIntegrationTest){

    const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: ID!): User} type User { id: ID! name: string!	age: Int}";

    const char * query = "query{user(id:1) {name}}";
    GraphqlCppApi *api = GraphqlCppApi::createInstance();
    api->setSchema(schema);
    api->registerResolver(new GraphQlResolverTestData::UserResolver());
    string response = (api->executeRequest(query));
    string expected = R"({"data":{"name":"Herbert"}})";
    checkIfStrEqu(expected, response);
}

TEST(IntegrationTest, multipleChildesAtRootLevel){

    const char* schema = "schema {query: Query, mutation: Mutation} type Query { allUsers: [User]} type User { id: ID! name: string!	age: Int}";

    const char * query = "query{ allUsers {name}}";
    GraphqlCppApi *api = GraphqlCppApi::createInstance();
    api->setSchema(schema);
    auto resolver = new GraphQlResolverTestData::AllUserResolver();
    api->registerResolver(resolver);
    string response = (api->executeRequest(query));
    string expected = R"({"data":[{"name":"Herbert"},{"name":"Herbert"},{"name":"Herbert"}]})";
    checkIfStrEqu(expected, response);
}

TEST(IntegrationTest, multipleChildes){

    const char* schema = "schema {query: Query } type Query { car: Car} type Car { wheels: [Wheel]} type Wheel {pressure:Int}";

    const char * query = "query{ car { wheels { pressure } } }";
    GraphqlCppApi *api = GraphqlCppApi::createInstance();
    api->setSchema(schema);
    auto resolver = new GraphQlResolverTestData::CarResolver();
    api->registerResolver(resolver);
    string response = (api->executeRequest(query));
    string expected = R"({"data":{"wheels":[{"pressure":1},{"pressure":2},{"pressure":3},{"pressure":4}]}})";
    checkIfStrEqu(expected, response);
}
//TODO test schreiben, ob nested listen typen also nicht auf root ebene auch funktionieren

TEST(GraphqlApiTest, finalDemoTest) {
    const char *schema = "schema {  query: Query }  type Query {  book(id: int!): Book  author(id: int!): Author }  type Book {  id: int!  title: String  published: String  price: String  authorOfBook: Author }  type Quote {  id: int!  quote: String }  type Author {  id: int!  firstName: String  lastName: String  quotes: [Quote] }";

    const char *query = "query{book(id:1){title, authorOfBook{firstName quotes{quote}}}}";
    GraphqlCppApi *api = ApiFactory::createApi();
    api->setSchema(schema);
    auto resolver = new GraphQlResolverTestData::BookResolver;
    api->registerResolver(resolver);
    std::string response = api->executeRequest(query);
    std::string expected = R"({"data":{"title":"Faust. Eine Tragödie.","authorOfBook":{"firstName":"Johann Wolfgang","quotes":[{"quote":"Mit dem Wissen wächst der Zweifel."},{"quote":"Wo viel Licht ist, ist starker Schatten."}]}}})";

    checkIfStrEqu(response, expected);
}