/*
 * GraphqlCppApi.cpp
 *
 *  Created on: 10.02.2019
 *      Author: admin
 */

#include "../../libgraphqlparser/Ast.h"
#include "../../libgraphqlparser/GraphQLParser.h"
#include "GraphqlCppApi.h"
#include "../../libgraphqlparser/c/GraphQLAstToJSON.h"
#include "../exceptions/NoSchemaSetException.h"
#include "../exceptions/InvalidSchemaException.h"

namespace graphqlcpp {
namespace api {
using namespace facebook::graphql;
using namespace graphqlcpp::exceptions;

GraphqlCppApi::GraphqlCppApi(SchemaValidator* sValidator,
		QueryValidator* queryValidator) {
	this->schemaValidator = sValidator;
	this->queryValidator = queryValidator;

}

void GraphqlCppApi::setSchema(const char* schema) {
	const char* err = "";
	auto sAst = parseString(schema, &err);
	Node* rootNode = sAst.get();
	if (schemaValidator->checkIfSchemaIsValid(rootNode)) {
		schemaAst = sAst.get();
	} else {
		throw InvalidSchemaException();
	}

}

const char* GraphqlCppApi::printSchemaAsJson() {
	const char *json = graphql_ast_to_json(
			(const struct GraphQLAstNode *) schemaAst);
	return json;
}

bool GraphqlCppApi::checkIfRequestValid(Node* rootNodeRequest) {
	if (schemaAst != nullptr) {
		return this->queryValidator->isQueryValid(schemaAst, rootNodeRequest);
	}
	throw NoSchemaSetException();
}

const char* GraphqlCppApi::executeQuery(const char* query) {
	Node* requestAst = parseStringToAst(query);
	if(checkIfRequestValid(requestAst)){
		return "request valid";
	}
	return "";
}
Node* GraphqlCppApi::parseStringToAst(const char* str) {
	const char* err = "";
	auto sAst = parseString(str, &err);
	Node* rootNode = sAst.get();
	return rootNode;
}
}
} /* namespace graphqlcppapi */


