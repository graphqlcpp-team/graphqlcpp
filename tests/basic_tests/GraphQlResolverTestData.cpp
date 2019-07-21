//
// Created by julian on 11.04.19.
//

#include <gtest/gtest.h>
#include "string"
//#include "jsoncpp/json/value.h"
//#include "jsoncpp/json/reader.h"
#include "../../include/graphqlcpp/utils/MySerializer.h"
#include "../../include/graphqlcpp/IGraphQlDTO.h"
#include "../../include/graphqlcpp/utils/MyWriter.h"
#include "../../src/graphqlparser/GraphQLParser.h"
#include "../../include/graphqlcpp/validators/QueryValidator.h"
#include "../../../include/graphqlparser/Ast.h"
#include "../../../include/graphqlcpp/validators/QueryValidator.h"
#include "../../src/graphqlparser/c/GraphQLAst.h"
#include "../../include/graphqlcpp/validators/SchemaAstWraper.h"
#include "../../include/graphqlcpp/resolver/IGraphQlResolver.h"
#include "../../include/graphqlcpp/GraphQlDTOSingleRoot.h"
#include "../../include/graphqlcpp/GraphQlDTOMultiRoot.h"
#include "TestData.cpp"

//using namespace Json;
using namespace std;
using namespace graphqlcpp::resolver;

namespace GraphQlResolverTestData {

    class ResolverOne : public graphqlcpp::resolver::IGraphQlResolver {
    private:
        IGraphQlDTO *dtoObject;
    public:

        ResolverOne() {
            dtoObject = new GraphQlDTOSingleRoot(demo::TestDataGenerator::createCustomer());
        }

        IGraphQlDTO * getDtoObject() {
            return dtoObject;
        }

        std::string getResolverName() override {
            return "user";
        }

        //TODO beachte es werden die serialisierten objekte nicht gelöscht
        IGraphQlDTO *execute(const std::vector<ResolverArgument *> *resolverArgs) override {

            return dtoObject;
        }

    };

    class UserResolver : public graphqlcpp::resolver::IGraphQlResolver {
    private:
        IGraphQlDTO *dtoObject;
    public:
        UserResolver() {
            dtoObject = new GraphQlDTOSingleRoot(demo::TestDataGenerator::createUser());
        }

        IGraphQlDTO * getDtoObject() {
            return dtoObject;
        }

        std::string getResolverName() override {
            return "user";
        }

        //TODO beachte es werden die serialisierten objekte nicht gelöscht
        IGraphQlDTO *execute(const std::vector<ResolverArgument *> *resolverArgs) override {
            return dtoObject;
        }

    };

    class AllUserResolver : public graphqlcpp::resolver::IGraphQlResolver {
    private:
        IGraphQlDTO *dtoObject;
    public:
        AllUserResolver() {
            vector<IGraphQlDTO*> users = vector<IGraphQlDTO*>();
            users.push_back(demo::TestDataGenerator::createUser());
            users.push_back(demo::TestDataGenerator::createUser());
            users.push_back(demo::TestDataGenerator::createUser());
            dtoObject = new GraphQlDTOMultiRoot(users);
        }

        IGraphQlDTO * getDtoObject() {
            return dtoObject;
        }

        std::string getResolverName() override {
            return "allUsers";
        }

        //TODO beachte es werden die serialisierten objekte nicht gelöscht
        IGraphQlDTO *execute(const std::vector<ResolverArgument *> *resolverArgs) override {
            return dtoObject;
        }

    };
    class BookResolver : public graphqlcpp::resolver::IGraphQlResolver {
    private:
        IGraphQlDTO *dtoObject;
    public:
        BookResolver() {
            vector<IGraphQlDTO*> v = demo::TestDataGenerator::createBooks();
            dtoObject = new GraphQlDTOMultiRoot(v);
        }

        IGraphQlDTO * getDtoObject() {
            return dtoObject;
        }

        std::string getResolverName() override {
            return "book";
        }

        //TODO beachte es werden die serialisierten objekte nicht gelöscht
        IGraphQlDTO *execute(const std::vector<ResolverArgument *> *resolverArgs) override {
            for (auto i : *resolverArgs) {
                if (i->getArgName() == "id") {
                    int value = atoi(i->getArgValue().c_str());
                    switch (value) {
                        case 1:
                            this->dtoObject = new GraphQlDTOSingleRoot(demo::TestDataGenerator::createBooks()[0]);
                            break;
                        case 2:
                            this->dtoObject = new GraphQlDTOSingleRoot(demo::TestDataGenerator::createBooks()[1]);
                            break;
                        case 3:
                            this->dtoObject = new GraphQlDTOSingleRoot(demo::TestDataGenerator::createBooks()[2]);
                            break;
                        case 4:
                            this->dtoObject = new GraphQlDTOSingleRoot(demo::TestDataGenerator::createBooks()[3]);
                            break;
                    }

                }
            }
            return dtoObject;
        }

    };

}