//
// Created by julian on 11.04.19.
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

//using namespace Json;
using namespace std;
using namespace graphqlcpp::api;


namespace demo {
    class City : public IGraphQlDTO {
    private:
        char *name;
        int plz;
    public:
        City(char *name, int plz) {
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

    class TestDataGenerator {
    public:
        static Customer *createCustomer() {
            City *c = new City("Nuernberg", 90429);
            Address *a = new Address(c, "Fuertherstr.");
            Customer *cu = new Customer("Sven Steuermann", 34, a);
            return cu;
        }
    };


}