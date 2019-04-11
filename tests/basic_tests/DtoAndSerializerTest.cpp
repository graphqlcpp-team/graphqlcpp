//
// Created by julian on 07.04.19.
//

#include <gtest/gtest.h>
#include "../../include/graphqlcpp/utils/MySerializer.h"
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

namespace demo {
    class City : public IGraphQlDTO {
    private:
        char *name;
        vector<int> plz;
    public:
        City(char *name, vector<int> plz) {
            this->name = name;
            this->plz = plz;
        }

        MySerializer *serialize(MySerializer *serializer) override {
            serializer->setVal("name", this->name);
            serializer->setVal("plz", this->plz);
            return serializer;
        }
    };

    class Address : public IGraphQlDTO {
    private:
        City *city;
        char *street;
    public:
        Address(City *city, char *street) {
            this->city = city;
            this->street = street;
        }

    private:
        MySerializer *serialize(MySerializer *serializer) override {
            serializer->setVal("city", this->city);
            serializer->setVal("street", this->street);
            return serializer;
        }
    };


    class Customer : public IGraphQlDTO {
    private:
        char *name;
        int age;
        Address *address;
    public:
        Customer(char *name, int age, Address *address) {
            this->name = name;
            this->age = age;
            this->address = address;
        }


        MySerializer *serialize(MySerializer *serializer) override {
            //TODO prüfen ob key z.B name wieder freigegeben wird am ende -> lint / tools zur laufzeitanalyse von speicher
            serializer->setVal("name", name);
            serializer->setVal("age", age);
            serializer->setVal("address", address);
            return serializer;
        }
    };

    Customer *createCustomer() {
        vector<int> plzs = {90, 80};
        City *c = new City("Nuernberg", plzs);
        Address *a = new Address(c, "Fuertherstr.");
        Customer *cu = new Customer("Sven Steuermann", 34, a);
        return cu;

    }
}

using namespace demo;

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


TEST(DtoAndSerializerTest, intVectorTest) {
    vector<int> array = {1, 2, 3,4, 5};
    MyWriter *writer = new  MyWriter();
    writer->appendValue("name", array);

    EXPECT_TRUE(writer->getJson() ==  "{\"name\":[1,2,3,4,5]}");
}

TEST(DtoAndSerializerTest, stringVectorTest) {
    vector<string> array = {"Eins", "Zwei", "Drei", "Vier", "Fuenf"};
    MyWriter *writer = new  MyWriter();
    writer->appendValue("name", array);
    EXPECT_TRUE(writer->getJson() ==  "{\"name\":[\"Eins\",\"Zwei\",\"Drei\",\"Vier\",\"Fuenf\"]}");
}
TEST(DtoAndSerializerTest, multipleStringVectorTest) {
    vector<string> array = {"Eins", "Zwei", "Drei", "Vier", "Fuenf"};
    vector<string> array2 = {"Eins", "Zwei", "Drei", "Vier", "Fuenf"};
    MyWriter *writer = new  MyWriter();
    writer->appendValue("name", array);
    writer->appendValue("name", array2);
    EXPECT_TRUE(writer->getJson() ==  "{\"name\":[\"Eins\",\"Zwei\",\"Drei\",\"Vier\",\"Fuenf\"],\"name\":[\"Eins\",\"Zwei\",\"Drei\",\"Vier\",\"Fuenf\"]}");
}

TEST(DtoAndSerializerTest, boolVectorTest) {
    vector<bool> array = {true, false, true, false, true};
    MyWriter *writer = new  MyWriter();
    writer->appendValue("name", array);
    EXPECT_TRUE(writer->getJson() ==  "{\"name\":[true,false,true,false,true]}");
}

TEST(DtoAndSerializerTest, writerVectorTest) {
    vector<bool> boolArray = {true, false, true, false, true};
    MyWriter *boolWriter = new  MyWriter();
    boolWriter->appendValue("name", boolArray);

    vector<string> stringArray = {"Eins", "Zwei", "Drei", "Vier", "Fuenf"};
    MyWriter *stringWriter = new  MyWriter();
    stringWriter->appendValue("name", stringArray);

    vector<string> stringArray2 = {"Eins", "Zwei", "Drei", "Vier", "Fuenf"};
    MyWriter *stringWriter2 = new  MyWriter();
    stringWriter2->appendValue("name", stringArray2);

    vector<int> intArray = {1, 2, 3,4, 5};
    MyWriter *intWriter = new  MyWriter();
    intWriter->appendValue("name", intArray);

    vector<MyWriter*> writerArray;
    writerArray.push_back(stringWriter);
    writerArray.push_back(boolWriter);
    writerArray.push_back(intWriter);

    MyWriter *writer = new  MyWriter();
    writer->appendVectorWritersValue("name", writerArray);
    cout << writer->getJson();
    EXPECT_TRUE(writer->getJson() ==  "{\"name\":[{\"name\":[\"Eins\",\"Zwei\",\"Drei\",\"Vier\",\"Fuenf\"]},{\"name\":[true,false,true,false,true]},{\"name\":[1,2,3,4,5]}]}");
}