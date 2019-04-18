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
#include "../../include/graphqlcpp/resolver/IGraphQlResolver.h"
#include "TestData.cpp"

//using namespace Json;
using namespace std;
using namespace graphqlcpp::resolver;

namespace GraphQlResolverTestData {

    class ResolverOne : public graphqlcpp::resolver::IGraphQlResolver {
    public:
        char *getResolverName() override {
            return "user";
        }

        //TODO beachte es werden die serialisierten objekte nicht gelöscht
        IGraphQlDTO *execute(const std::vector<ResolverArgument *> *resolverArgs) override {
            return demo::TestDataGenerator::createCustomer();
        }

    };
}