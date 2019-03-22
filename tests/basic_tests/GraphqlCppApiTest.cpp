#include"gtest/gtest.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../../include/graphqlcpp/GraphqlCppApi.h"
#include "../../include/graphqlcpp/ApiFactory.h"


using namespace std;
using namespace facebook::graphql;
using namespace facebook::graphql::ast;
using namespace graphqlcpp::api;

TEST(GraphQlApiTest, dumpAstAsJson){

	const char* simpleSchema = "{ me { name } }";

	GraphqlCppApi* api = ApiFactory::createApi();
	api->setSchema(simpleSchema);
	//auto json = api->printSchemaAsJson();
	//cout << json;
	//ASSERT_NE(nullptr, json);

}

