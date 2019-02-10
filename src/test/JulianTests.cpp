#include"../../gtest/gtest.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../libgraphqlparser/Ast.h"
#include "../libgraphqlparser/GraphQLParser.h"
#include "../libgraphqlparser/c/GraphQLAstToJSON.h"

using namespace std;
using namespace facebook::graphql;
using namespace facebook::graphql::ast;

#include <stdio.h>  /* defines FILENAME_MAX */



static const char* dumpJson(const char* graqhqlquery){
	const char* err = "";
	auto ast = parseString(graqhqlquery, &err);
	const char* json = graphql_ast_to_json((const struct GraphQLAstNode *)ast.get());
	cout << err << endl;
	return json;
}

TEST(julianstests, openfile){
	 FILE * pFile;
	 pFile = fopen ("./kitchen-sink.graphql","r");
	 ASSERT_TRUE(pFile != NULL);
	 ASSERT_NE(nullptr, pFile);
	 pFile = fopen ("kitchen-sink.graphql","r");
	 ASSERT_TRUE(pFile != NULL);
	 ASSERT_NE(nullptr, pFile);
	 pFile = fopen (".\\kitchen-sink.graphql","r");
	 ASSERT_TRUE(pFile != NULL);
	 ASSERT_NE(nullptr, pFile);
}


TEST(julianstests, dumpAstAsJson){
	const char* jsonAST = "{\"kind\":\"Document\",\"loc\":{\"start\": {\"line\": 1,\"column\":1}, \"end\": {\"line\":1,\"column\":16}},\"definitions\":[{\"kind\":\"OperationDefinition\",\"loc\":{\"start\": {\"line\": 1,\"column\":1}, \"end\": {\"line\":1,\"column\":16}},\"operation\":\"query\",\"name\":null,\"variableDefinitions\":null,\"directives\":null,\"selectionSet\":{\"kind\":\"SelectionSet\",\"loc\":{\"start\": {\"line\": 1,\"column\":1}, \"end\": {\"line\":1,\"column\":16}},\"selections\":[{\"kind\":\"Field\",\"loc\":{\"start\": {\"line\": 1,\"column\":3}, \"end\": {\"line\":1,\"column\":14}},\"alias\":null,\"name\":{\"kind\":\"Name\",\"loc\":{\"start\": {\"line\": 1,\"column\":3}, \"end\": {\"line\":1,\"column\":5}},\"value\":\"me\"},\"arguments\":null,\"directives\":null,\"selectionSet\":{\"kind\":\"SelectionSet\",\"loc\":{\"start\": {\"line\": 1,\"column\":6}, \"end\": {\"line\":1,\"column\":14}},\"selections\":[{\"kind\":\"Field\",\"loc\":{\"start\": {\"line\": 1,\"column\":8}, \"end\": {\"line\":1,\"column\":12}},\"alias\":null,\"name\":{\"kind\":\"Name\",\"loc\":{\"start\": {\"line\": 1,\"column\":8}, \"end\": {\"line\":1,\"column\":12}},\"value\":\"name\"},\"arguments\":null,\"directives\":null,\"selectionSet\":null}]}}]}}]}";

	cout << "testStarted";
	const char* simpleSchema = "{ me { name } }";
	const char* json = dumpJson(simpleSchema);
	cout << json << endl;
	ASSERT_TRUE(json!=nullptr);

}
