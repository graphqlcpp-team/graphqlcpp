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
#include <vector>
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

    class Wheel : public IGraphQlDTO {
    private:
        int pressure;
    public:
        Wheel(int pressure) {
            this->pressure = pressure;
        }

        MySerializer *serialize(MySerializer *serializer) override {
            serializer->setVal("pressure", this->pressure);
            return serializer;
        }
    };


    class Car : public IGraphQlDTO {
    private:
        vector<Wheel*> wheels;
    public:
        Car(vector<Wheel*> wheels) {
            this->wheels = wheels;
        }

        MySerializer *serialize(MySerializer *serializer) override {
            vector<IGraphQlDTO*> vec(wheels.begin(), wheels.end());
            serializer->setVal("wheels", vec);
            return serializer;
        }
    };



    class Quote : public IGraphQlDTO {
    private:
        int id;
        std::string quote;

    public:
        Quote(int id, std::string quote) {
            this->id = id;
            this->quote = quote;
        }

        MySerializer *serialize(MySerializer *serializer) override {
            serializer->setVal("id", this->id);
            serializer->setVal("quote", this->quote);
            return serializer;
        }
    };

    class Author : public IGraphQlDTO {
    private:
        int id;
        std::string firstName;
        std::string lastName;
        std::vector<IGraphQlDTO*> quotes;
    public:
        Author(int id, std::string firstName, std::string lastName, vector<IGraphQlDTO*> quotes) {
            this->id = id;
            this->firstName = firstName;
            this->lastName = lastName;
            this->quotes = vector<IGraphQlDTO*>(quotes.begin(), quotes.end());
        }

        MySerializer *serialize(MySerializer *serializer) override {
            serializer->setVal("id", this->id);
            serializer->setVal("firstName", this->firstName);
            serializer->setVal("lastName", this->lastName);
            serializer->setVal("quotes", this->quotes);
            return serializer;
        }
    };

    class Book : public IGraphQlDTO {
    private:
        int id;
        std::string title;
        std::string published;
        std::string price;
        Author *authorOfBook;
    public:
        Book(int id, std::string title, std::string published, std::string price, Author *author) {
            this->id = id;
            this->title = title;
            this->published = published;
            this->price = price;
            this->authorOfBook = author;
        }

        MySerializer *serialize(MySerializer *serializer) override {
            serializer->setVal("id", this->id);
            serializer->setVal("title", this->title);
            serializer->setVal("published", this->published);
            serializer->setVal("price", this->price);
            serializer->setVal("authorOfBook", this->authorOfBook);
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

        static IGraphQlDTO *createCar(){
            std::vector<Wheel*> vw ;

            Wheel* w1 = new Wheel(1);
            vw.push_back(w1);
            Wheel* w2 = new Wheel(2);
            vw.push_back(w2);
            Wheel* w3 = new Wheel(3);
            vw.push_back(w3);
            Wheel* w4 = new Wheel(4);
            vw.push_back(w4);

            return new Car(vw);
        }
        static vector<IGraphQlDTO *> createBooks(){
            Quote *q1 = new Quote(1, "Mit dem Wissen wächst der Zweifel.");
            Quote *q2 = new Quote(2, "Wo viel Licht ist, ist starker Schatten.");
            vector<IGraphQlDTO *> qs;
            qs.push_back(q1);
            qs.push_back(q2);
            Author * a1 = new Author(1, "Johann Wolfgang", "von Goethe", qs);
            Book *b1 = new Book(1, "Faust. Eine Tragödie.", "1808", "unbezahlbar", a1);
            Book *b2 = new Book(2, "Faust. Der Tragödie zweiter Teil", "1832", "unbezahlbar", a1);
            vector<IGraphQlDTO *> bs;
            bs.push_back(b1);
            bs.push_back(b2);

            Quote *q3 = new Quote(3, "Man sollt' den Tag nicht vor dem Abend loben.");
            Quote *q4 = new Quote(4, "Erst handeln und dann reden.");
            vector<IGraphQlDTO *> qf;
            qf.push_back(q3);
            qf.push_back(q4);
            Author * a2 = new Author(2, "Friedrich", "Schiller", qf);
            Book *b3 = new Book(3, "Die Räuber", "1782", "unbezahlbar", a2);
            Book *b4 = new Book(4, "Wallenstein", "1800", "unbezahlbar", a2);
            bs.push_back(b3);
            bs.push_back(b4);
            return bs;
        }

    };


}