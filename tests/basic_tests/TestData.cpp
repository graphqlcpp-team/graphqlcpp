//
// Created by julian on 11.04.19.
//

#include <gtest/gtest.h>
//#include "jsoncpp/json/value.h"
//#include "jsoncpp/json/reader.h"
#include "../../include/graphqlcpp/utils/MySerializer.h"
#include "../../include/graphqlcpp/IGraphQlDTO.h"
#include "../../include/graphqlcpp/GraphQlDTOSingleRoot.h"
#include "../../include/graphqlcpp/utils/MySerializer.h"
#include "../../include/graphqlcpp/IGraphQlDTO.h"
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
        std::string name;
        vector<int> plz;
    public:
        City(std::string name, vector<int> plz) {
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
        std::string street;
    public:
        Address(City *city, std::string street) {
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
        std::string name;
        int age;
        Address *addressFirst;
        Address *addressSecond;
    public:
        Customer(std::string name, int age, Address *addressFirst, Address *second) {
            this->name = name;
            this->age = age;
            this->addressFirst = addressFirst;
            this->addressSecond = second;
        }


        MySerializer *serialize(MySerializer *serializer) override {
            //TODO prüfen ob key z.B name wieder freigegeben wird am ende -> lint / tools zur laufzeitanalyse von speicher
            serializer->setVal("name", name);
            serializer->setVal("addressFirst", addressFirst);
            serializer->setVal("age", age);
            serializer->setVal("addressSecond", addressSecond);
            return serializer;
        }
    };

    class User : public IGraphQlDTO {
    private:
        int id;
        std::string name;
    public:
        User(std::string name,int id) {
            this->name = name;
            this->id = id;
        }

        MySerializer *serialize(MySerializer *serializer) override {
            serializer->setVal("id", this->id);
            serializer->setVal("name", this->name);
            return serializer;
        }
    };

    class TestDataGenerator {
    public:
        static IGraphQlDTO *createCustomer() {
            City *c = new City("Nuernberg", {90429} );
            City *c2 = new City("Munic", {90429} );
            Address *a1 = new Address(c, "Fuertherstr.");
            Address *a2 = new Address(c2, "Maximilanstr.");
            Customer *cu = new Customer("Sven Steuermann", 34, a1, a2);
            return cu;
        }
        static IGraphQlDTO *createUser(){
            return new User("Herbert", 1);
        }
    };


}