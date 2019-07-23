//
// Created by julian on 07.04.19.
//

#include <gtest/gtest.h>
#include "../../include/graphqlcpp/utils/MySerializerRoot.h"
#include "../../include/graphqlcpp/IGraphQlDTO.h"
#include "../../include/graphqlcpp/utils/MyWriter.h"
#include "../../src/graphqlparser/GraphQLParser.h"
#include "../../include/graphqlcpp/validators/QueryValidator.h"
#include "../../../include/graphqlparser/Ast.h"
#include "../../../include/graphqlcpp/validators/QueryValidator.h"
#include "../../src/graphqlparser/c/GraphQLAst.h"
#include "../../include/graphqlcpp/validators/SchemaAstWraper.h"
#include "TestData.cpp"

using namespace std;
using namespace graphqlcpp::api;


TEST(DtoAndSerializerTest, wasFieldRequested) {
    IGraphQlDTO *c = demo::TestDataGenerator::createCustomer();

    const char * error = nullptr;
    const char * query = "query{name, addressFirst {city {plz, name}} age}";
    std::unique_ptr<Node> queryAst;
    queryAst = facebook::graphql::parseString(query, &error);
    Node * rootNodeQuery = queryAst.get();
    graphqlcpp::validators::SchemaAstWraper* saw = new graphqlcpp::validators::SchemaAstWraper(queryAst.get());
    graphqlcpp::validators::QueryValidator* qv = new graphqlcpp::validators::QueryValidator(saw);
    const SelectionSet *selectionSet = qv->getSelectionSet(rootNodeQuery);

    MySerializer *ser = new MySerializerRoot(selectionSet);
    ser = c->serialize(ser);
    MyWriter writer = ser->createJson();
    cout << writer.getJson();
}


TEST(DtoAndSerializerTest, wasFieldRequestedTwoObjects) {
    IGraphQlDTO *c = demo::TestDataGenerator::createCustomer();

    const char * error = nullptr;
    const char * query = "query{addressSecond {city {plz, name}} name addressFirst {city {plz, name}} age}";
    std::unique_ptr<Node> queryAst;
    queryAst = facebook::graphql::parseString(query, &error);
    Node * rootNodeQuery = queryAst.get();
    graphqlcpp::validators::SchemaAstWraper* saw = new graphqlcpp::validators::SchemaAstWraper(queryAst.get());
    graphqlcpp::validators::QueryValidator* qv = new graphqlcpp::validators::QueryValidator(saw);
    const SelectionSet *selectionSet = qv->getSelectionSet(rootNodeQuery);

    MySerializer *ser = new MySerializerRoot(selectionSet);
    ser = c->serialize(ser);
    MyWriter writer = ser->createJson();
    cout << writer.getJson();
}

TEST(DtoAndSerializerTest, intVectorTest) {
    vector<int> array = {1, 2, 3,4, 5};
    MyWriter writer= MyWriter();
    writer.appendValue("name", array);

    EXPECT_TRUE(writer.getJson() ==  "{\"name\":[1,2,3,4,5]}");
}

TEST(DtoAndSerializerTest, stringVectorTest) {
    vector<string> array = {"Eins", "Zwei", "Drei", "Vier", "Fuenf"};
    MyWriter writer= MyWriter();
    writer.appendValue("name", array);
    EXPECT_TRUE(writer.getJson() ==  "{\"name\":[\"Eins\",\"Zwei\",\"Drei\",\"Vier\",\"Fuenf\"]}");
}
TEST(DtoAndSerializerTest, multipleStringVectorTest) {
    vector<string> array = {"Eins", "Zwei", "Drei", "Vier", "Fuenf"};
    vector<string> array2 = {"Eins", "Zwei", "Drei", "Vier", "Fuenf"};
    MyWriter writer= MyWriter();
    writer.appendValue("name", array);
    writer.appendValue("name", array2);
    EXPECT_TRUE(writer.getJson() ==  "{\"name\":[\"Eins\",\"Zwei\",\"Drei\",\"Vier\",\"Fuenf\"],\"name\":[\"Eins\",\"Zwei\",\"Drei\",\"Vier\",\"Fuenf\"]}");
}

TEST(DtoAndSerializerTest, boolVectorTest) {
    vector<bool> array = {true, false, true, false, true};
    MyWriter writer= MyWriter();
    writer.appendValue("name", array);
    EXPECT_TRUE(writer.getJson() ==  "{\"name\":[true,false,true,false,true]}");
}

TEST(DtoAndSerializerTest, writerVectorTest) {
    vector<bool> boolArray = {true, false, true, false, true};
    MyWriter boolWriter= MyWriter();
    boolWriter.appendValue("name", boolArray);

    vector<string> stringArray = {"Eins", "Zwei", "Drei", "Vier", "Fuenf"};
    MyWriter stringWriter= MyWriter();
    stringWriter.appendValue("name", stringArray);

    vector<string> stringArray2 = {"Eins", "Zwei", "Drei", "Vier", "Fuenf"};
    MyWriter stringWriter2= MyWriter();
    stringWriter2.appendValue("name", stringArray2);

    vector<int> intArray = {1, 2, 3,4, 5};
    MyWriter intWriter= MyWriter();
    intWriter.appendValue("name", intArray);

    vector<MyWriter> writerArray;
    writerArray.push_back(stringWriter);
    writerArray.push_back(boolWriter);
    writerArray.push_back(intWriter);

    MyWriter writer = MyWriter();
    writer.appendVectorWritersValue(std::string("name"), writerArray);
    cout << writer.getJson();
    EXPECT_TRUE(writer.getJson() ==  "{\"name\":[{\"name\":[\"Eins\",\"Zwei\",\"Drei\",\"Vier\",\"Fuenf\"]},{\"name\":[true,false,true,false,true]},{\"name\":[1,2,3,4,5]}]}");
}