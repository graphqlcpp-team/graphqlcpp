/*
 * GraphqlCppApi.cpp
 *
 *  Created on: 10.02.2019
 *      Author: admin
 */

#include "libgraphqlparser/Ast.h"
#include "libgraphqlparser/GraphQLParser.h"
#include "GraphqlCppApi.h"
#include "libgraphqlparser/c/GraphQLAstToJSON.h"

namespace graphqlcpp {
namespace api {
using namespace facebook::graphql;

GraphqlCppApi::GraphqlCppApi(SchemaValidator* sValidator) {
	schemaValidator = sValidator;

}

void GraphqlCppApi::setSchema(const char* schema) {
	const char* err = "";
	auto sAst = parseString(schema, &err);
	Node* rootNode = sAst.get();
	if(schemaValidator->checkIfSchemaIsValid(rootNode)){
		schemaAst = sAst.get();
	}

}

const char* GraphqlCppApi::printSchemaAsJson() {
	const char *json = graphql_ast_to_json((const struct GraphQLAstNode *)schemaAst);
	return json;
}

bool GraphqlCppApi::checkIfRequestValid(const char* request) {
}
}
} /* namespace graphqlcppapi */
