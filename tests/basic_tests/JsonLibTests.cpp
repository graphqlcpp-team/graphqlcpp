
#include <gtest/gtest.h>
#include "jsoncpp/json/value.h"
#include "jsoncpp/json/reader.h"


using namespace Json;
using namespace std;


namespace demo {


    class IGraphQlDTO {
    public:
        virtual Json::Value asJson() = 0;

        virtual char *getDTOType() = 0;

    protected:
        IGraphQlDTO(Json::Value json) {
        }

        IGraphQlDTO() {};
    };

    class UserDTO : IGraphQlDTO {

    private:
        String name;
        int age;
        bool male;
    public:
        const String &getName() const {
            return name;
        }

        int getAge() const {
            return age;
        }

        bool isMale() const {
            return male;
        }

    public:
        UserDTO(const Value &json) : IGraphQlDTO(json) {
            this->name = json["name"].asString();
            this->age = json["age"].asInt();
            this->male = json["male"].asBool();
        }

        UserDTO(const String &name, int age, bool male) : name(name), age(age), male(male) {}

        Value asJson() override {
            Json::Value json;
            json["name"] = name;
            json["age"] = age;
            json["male"] = male;

            return json;
        }

        char *getDTOType() override {
            return "User";
        }
    };
}

TEST(JSONLibTests, tryToDeserialize) {

    auto json = "{ \"name\": \"julian\", \"age\": 23, \"male\": true }";
    Json::Value test;
    Json::Reader reader;
    reader.parse(json, test);
    auto name = test["name"].asCString();
    cout << name;
}

TEST(JSONLibTests, tryToDeserializeToObject) {

    auto json = "{ \"name\": \"julian\", \"age\": 23, \"male\": true }";
    Json::Value test;
    Json::Reader reader;
    reader.parse(json, test);
    demo::UserDTO* userDTO = new demo::UserDTO(test);
    ASSERT_EQ("julian", userDTO->getName() );
}


TEST(JSONLibTests, manipulateJson) {

    auto json = "{ \"name\": \"julian\", \"age\": 23, \"male\": true, \"demo\":{\"test\":\"jaa\"} }";
    Json::Value test;
    Json::Reader reader;
    reader.parse(json, test);

    Path* p = new Path(".demo.test");

    const Value &valueFromTest = p->resolve(test);
    auto str = valueFromTest.asCString();
    
    test["foo.bar"] = 17;

    const char *bla = test["foo"]["bar"].asCString();

    ASSERT_EQ(test, test);



}
