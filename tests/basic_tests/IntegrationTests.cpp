#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "../../include/graphqlcpp/GraphqlCppApi.h"
#include "GraphQlResolverTestData.cpp"
#include"gtest/gtest.h"
#include <stdio.h>  /* defines FILENAME_MAX */
#include <chrono>

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
    cout << "Checking if Query is valid at: ";
    auto start = std::chrono::system_clock::now();
    GraphqlCppApi *api = GraphqlCppApi::createInstance();
    api->setSchema(schema);
    api->registerResolver(new GraphQlResolverTestData::UserResolver());
    string response = (api->executeRequest(query));
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";

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

TEST(IntegrationTest, finalDemoTest) {
    const char *schema = "schema {  query: Query }  type Query {  book(id: int!): Book  author(id: int!): Author }  type Book {  id: int!  title: String  published: String  price: String  authorOfBook: Author }  type Quote {  id: int!  quote: String }  type Author {  id: int!  firstName: String  lastName: String  quotes: [Quote] }";

    const char *query = "query{book(id:1){title, authorOfBook{firstName quotes{quote}}}}";
    GraphqlCppApi *api = GraphqlCppApi::createInstance();
    api->setSchema(schema);
    auto resolver = new GraphQlResolverTestData::BookResolver;
    api->registerResolver(resolver);
    std::string response = api->executeRequest(query);
    std::string expected = R"({"data":{"title":"Faust. Eine Tragödie.","authorOfBook":{"firstName":"Johann Wolfgang","quotes":[{"quote":"Mit dem Wissen wächst der Zweifel."},{"quote":"Wo viel Licht ist, ist starker Schatten."}]}}})";

    ASSERT_EQ(response, expected);
    delete api;
}

TEST(IntegrationTest, lastTemperatureMeasurementsTest){
    const char *schema = "schema {   query: Query }  type Temperature {   date: String   temperature: Float } type AirPressure {   date: String   pressure: Float }   type Query {   lastTemperatureMeasurements(last:Int!): [Temperature]   averageTemperature(date: String!): Temperature      lastAirPressureMeasurements(last:Int!): [AirPressure]   averageAirPressure(date: String!): AirPressure }";
    const char *query = "query{lastTemperatureMeasurements(last:2){temperature}}";

    GraphqlCppApi *api = GraphqlCppApi::createInstance();
    api->setSchema(schema);
    auto resolver = new GraphQlResolverTestData::LastTemperatureMeasurementsResolver;
    api->registerResolver(resolver);
    std::string response = api->executeRequest(query);
    std::string expected = R"({"data":[{"temperature":20.400000},{"temperature":28.000000}]})";

    ASSERT_EQ(response, expected);
    delete api;
}

TEST(IntegrationTest, lastAirPressureMeasurementsTest){
    const char *schema = "schema {   query: Query }  type Temperature {   date: String   temperature: Float } type AirPressure {   date: String   pressure: Float }   type Query {   lastTemperatureMeasurements(last:Int!): [Temperature]   averageTemperature(date: String!): Temperature      lastAirPressureMeasurements(last:Int!): [AirPressure]   averageAirPressure(date: String!): AirPressure }";
    const char *query = "query{lastAirPressureMeasurements(last:2){pressure}}";

    GraphqlCppApi *api = GraphqlCppApi::createInstance();
    api->setSchema(schema);
    auto resolver = new GraphQlResolverTestData::LastAirPressureMeasurementsResolver;
    api->registerResolver(resolver);
    std::string response = api->executeRequest(query);
    std::string expected = R"({"data":[{"pressure":10000.230469},{"pressure":99999.203125}]})";

    ASSERT_EQ(response, expected);
    delete api;
}

TEST(IntegrationTest, averageTemperatureTest){
    const char *schema = "schema {   query: Query }  type Temperature {   date: String   temperature: Float } type AirPressure {   date: String   pressure: Float }   type Query {   lastTemperatureMeasurements(last:Int!): [Temperature]   averageTemperature(date: String!): Temperature      lastAirPressureMeasurements(last:Int!): [AirPressure]   averageAirPressure(date: String!): AirPressure }";
    const char *query = "query{averageTemperature(date:\"01.01.1970\"){temperature}}";

    GraphqlCppApi *api = GraphqlCppApi::createInstance();
    api->setSchema(schema);
    auto resolver = new GraphQlResolverTestData::AverageTemperatureResolver;
    api->registerResolver(resolver);
    std::string response = api->executeRequest(query);
    std::string expected = R"({"data":{"temperature":20.400000}})";

    ASSERT_EQ(response, expected);

    delete api;
}

TEST(IntegrationTest, averageAirPressureTest){
    const char *schema = "schema {   query: Query }  type Temperature {   date: String   temperature: Float } type AirPressure {   date: String   pressure: Float }   type Query {   lastTemperatureMeasurements(last:Int!): [Temperature]   averageTemperature(date: String!): Temperature      lastAirPressureMeasurements(last:Int!): [AirPressure]   averageAirPressure(date: String!): AirPressure }";
    const char *query = "query{averageAirPressure(date:\"01.01.1970\"){pressure}}";

    GraphqlCppApi *api = GraphqlCppApi::createInstance();
    api->setSchema(schema);
    auto resolver = new GraphQlResolverTestData::AverageAirPressureResolver;
    api->registerResolver(resolver);
    std::string response = api->executeRequest(query);
    delete api;
}