//
// Created by julian on 07.04.19.
//

#include <gtest/gtest.h>
//#include "jsoncpp/json/value.h"
//#include "jsoncpp/json/reader.h"
#include "../../include/graphqlcpp/utils/MySerializer.h";
#include "../../include/graphqlcpp/IGraphQlDTO.h";
#include "../../include/graphqlcpp/utils/MyWriter.h"
#include "../../src/graphqlparser/GraphQLParser.h"
#include "../../include/graphqlcpp/validators/QueryValidator.h"
#include "../../../include/graphqlparser/Ast.h"
#include "../../../include/graphqlcpp/validators/QueryValidator.h"
#include "../../src/graphqlparser/c/GraphQLAst.h"
#include "../../include/graphqlcpp/validators/SchemaAstWraper.h"
#include "TestData.cpp"

//using namespace Json;
using namespace std;
using namespace graphqlcpp::api;


/*
TEST(DtoAndSerializerTest, simpleSerializaiton) {
    Customer *c = createCustomer();
    MySerializer *ser = new MySerializer(nullptr);
    ser = c->serialize(ser);
    MyWriter *writer = ser->createJson();
    cout << writer->getJson();

}*/





TEST(DtoAndSerializerTest, wasFieldRequested) {
    demo::Customer *c = demo::TestDataGenerator::createCustomer();

    const char * error = nullptr;
    const char * query = "query{name, address {city {plz, name}}}";
    std::unique_ptr<Node> queryAst;
    queryAst = facebook::graphql::parseString(query, &error);
    Node * rootNodeQuery = queryAst.get();
    graphqlcpp::validators::SchemaAstWraper* saw = new graphqlcpp::validators::SchemaAstWraper(queryAst.get());
    graphqlcpp::validators::QueryValidator* qv = new graphqlcpp::validators::QueryValidator(saw);
    const SelectionSet *selectionSet = qv->getSelectionSet(rootNodeQuery);

    MySerializer *ser = new MySerializer(selectionSet);
    ser = c->serialize(ser);
    MyWriter *writer = ser->createJson();
    cout << writer->getJson();
}