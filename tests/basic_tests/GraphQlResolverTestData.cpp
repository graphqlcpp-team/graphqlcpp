//
// Created by julian on 11.04.19.
//

#include <gtest/gtest.h>
#include "string"
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

        IGraphQlDTO *getDtoObject() {
            return dtoObject;
        }

        std::string getResolverName() override {
            return "user";
        }

        IGraphQlDTO *execute(const std::vector<ResolverArgument> resolverArgs) override {
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

        IGraphQlDTO *getDtoObject() {
            return dtoObject;
        }

        std::string getResolverName() override {
            return "user";
        }

        IGraphQlDTO *execute(const std::vector<ResolverArgument> resolverArgs) override {
            return dtoObject;
        }

    };

    class AllUserResolver : public graphqlcpp::resolver::IGraphQlResolver {
    private:
        IGraphQlDTO *dtoObject;
    public:
        AllUserResolver() {
            vector<IGraphQlDTO *> users = vector<IGraphQlDTO *>();
            users.push_back(demo::TestDataGenerator::createUser());
            users.push_back(demo::TestDataGenerator::createUser());
            users.push_back(demo::TestDataGenerator::createUser());
            dtoObject = new GraphQlDTOMultiRoot(users);
        }

        IGraphQlDTO *getDtoObject() {
            return dtoObject;
        }

        std::string getResolverName() override {
            return "allUsers";
        }

        IGraphQlDTO *execute(const std::vector<ResolverArgument> resolverArgs) override {
            return dtoObject;
        }


    };

    class CarResolver : public graphqlcpp::resolver::IGraphQlResolver {
    private:
        IGraphQlDTO *dtoObject;
    public:
        CarResolver() {
            this->dtoObject = new GraphQlDTOSingleRoot(demo::TestDataGenerator::createCar());
        }

        IGraphQlDTO *getDtoObject() {
            return dtoObject;
        }

        std::string getResolverName() override {
            return "car";
        }

        IGraphQlDTO *execute(const std::vector<ResolverArgument> resolverArgs) override {
            return dtoObject;
        }

    };

    class BookResolver : public graphqlcpp::resolver::IGraphQlResolver {
    private:
        IGraphQlDTO *dtoObject;
    public:
        BookResolver() {
            vector<IGraphQlDTO *> v = demo::TestDataGenerator::createBooks();
            dtoObject = new GraphQlDTOMultiRoot(v);
        }

        IGraphQlDTO *getDtoObject() {
            return dtoObject;
        }

        std::string getResolverName() override {
            return "book";
        }

        IGraphQlDTO *execute(const std::vector<ResolverArgument> resolverArgs) override {
            for (auto i : resolverArgs) {
                if (i.getArgName() == "id") {
                    int value = atoi(i.getArgValue().c_str());
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

    class LastTemperatureMeasurementsResolver : public graphqlcpp::resolver::IGraphQlResolver {
    private:
        IGraphQlDTO *dtoObject;
    public:
        LastTemperatureMeasurementsResolver() {
        }

        IGraphQlDTO *getDtoObject() {
            return dtoObject;
        }

        std::string getResolverName() override {
            return "lastTemperatureMeasurements";
        }

        IGraphQlDTO *execute(const std::vector<ResolverArgument> resolverArgs) override {
            for (auto i : resolverArgs) {
                if (i.getArgName() == "last") {
                    int value = atoi(i.getArgValue().c_str());
                    if (value == 2) {
                        this->dtoObject = new GraphQlDTOMultiRoot(demo::TestDataGenerator::createTemperature());
                    }

                }
            }
            return dtoObject;
        }

    };
    class LastAirPressureMeasurementsResolver : public graphqlcpp::resolver::IGraphQlResolver {
    private:
        IGraphQlDTO *dtoObject;
    public:
        LastAirPressureMeasurementsResolver() {
        }

        IGraphQlDTO *getDtoObject() {
            return dtoObject;
        }

        std::string getResolverName() override {
            return "lastAirPressureMeasurements";
        }

        IGraphQlDTO *execute(const std::vector<ResolverArgument> resolverArgs) override {
            for (auto i : resolverArgs) {
                if (i.getArgName() == "last") {
                    int value = atoi(i.getArgValue().c_str());
                    if (value == 2) {
                        this->dtoObject = new GraphQlDTOMultiRoot(demo::TestDataGenerator::createAirPressure());
                    }

                }
            }
            return dtoObject;
        }

    };

    class AverageTemperatureResolver : public graphqlcpp::resolver::IGraphQlResolver {
    private:
        IGraphQlDTO *dtoObject;
    public:
        AverageTemperatureResolver() {
        }

        IGraphQlDTO *getDtoObject() {
            return dtoObject;
        }

        std::string getResolverName() override {
            return "averageTemperature";
        }

        IGraphQlDTO *execute(const std::vector<ResolverArgument> resolverArgs) override {
            for (auto i : resolverArgs) {
                if (i.getArgName() == "date") {
                    std::string value = i.getArgValue().c_str();
                    if (value == "01.01.1970") {
                        this->dtoObject = new GraphQlDTOSingleRoot(demo::TestDataGenerator::createAverageTemperature());
                    }

                }
            }
            return dtoObject;
        }

    };

    class AverageAirPressureResolver : public graphqlcpp::resolver::IGraphQlResolver {
    private:
        IGraphQlDTO *dtoObject;
    public:
        AverageAirPressureResolver() {
        }

        IGraphQlDTO *getDtoObject() {
            return dtoObject;
        }

        std::string getResolverName() override {
            return "averageAirPressure";
        }

        IGraphQlDTO *execute(const std::vector<ResolverArgument> resolverArgs) override {
            for (auto i : resolverArgs) {
                if (i.getArgName() == "date") {
                    std::string value = i.getArgValue().c_str();
                    if (value == "01.01.1970") {
                        this->dtoObject = new GraphQlDTOSingleRoot(demo::TestDataGenerator::createAverageAirPressure());
                    }

                }
            }
            return dtoObject;
        }

    };
}