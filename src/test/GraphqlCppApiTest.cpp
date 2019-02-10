#include"../../gtest/gtest.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../libgraphqlparser/Ast.h"
#include "../libgraphqlparser/GraphQLParser.h"
#include "../libgraphqlparser/c/GraphQLAstToJSON.h"
#include "../GraphqlCppApi.h"

using namespace std;
using namespace facebook::graphql;
using namespace facebook::graphql::ast;
using namespace graphqlcppapi;


TEST(GraphQlApiTest, dumpAstAsJson){

	const char* simpleSchema = "{ me { name } }";
	GraphqlCppApi api;
	api.setSchema(simpleSchema);
	auto json = api.printSchemaAsJson();
	cout << json;

}

