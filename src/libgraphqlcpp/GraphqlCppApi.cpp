/*
 * GraphqlCppApi.cpp
 *
 *  Created on: 10.02.2019
 *      Author: admin
 */

#include "../libgraphqlparser/Ast.h"
#include "../libgraphqlparser/GraphQLParser.h"
#include "GraphqlCppApi.h"
#include "../libgraphqlparser/c/GraphQLAstToJSON.h"
#include "NoSchemaSetException.h"
#include "InvalidSchemaException.h"

namespace graphqlcpp {
namespace api {
using namespace facebook::graphql;
using namespace graphqlcpp::exceptions;

GraphqlCppApi::GraphqlCppApi() {
	this->schemaValidator = new SchemaValidator();
}

void GraphqlCppApi::setSchema(const char* schema) {
	auto rootNode = parseStringToAst(schema);
	if (schemaValidator->checkIfSchemaIsValid(rootNode)) {
		schemaWraper = new SchemaAstWraper(rootNode);
		queryValidator = new QueryValidator(schemaWraper);
	} else {
		throw InvalidSchemaException();
	}
}

bool GraphqlCppApi::checkIfRequestValid(Node* rootNodeRequest) {
	if (queryValidator != nullptr) {
		return this->queryValidator->isQueryValid(rootNodeRequest);
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
	//TODO check error string
	const char* err = "";
	auto sAst = parseString(str, &err);
	Node* rootNode = sAst.get();
	return rootNode;
}

const char* GraphqlCppApi::printSchemaAsJson() {
	if(schemaWraper!=nullptr){
		return schemaWraper->printSchemaAsJson();
	}
	throw NoSchemaSetException();
}

GraphqlCppApi::~GraphqlCppApi() {
	delete schemaWraper;
	delete schemaValidator;
	delete queryValidator;
}
}
} /* namespace graphqlcppapi */

