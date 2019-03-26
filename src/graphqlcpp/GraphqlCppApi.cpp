/*
 * GraphqlCppApi.cpp
 *
 *  Created on: 10.02.2019
 *      Author: admin
 */


#include "../graphqlparser/GraphQLParser.h"
#include "../../include/graphqlcpp/GraphqlCppApi.h"
#include "../graphqlparser/c/GraphQLAstToJSON.h"
#include "../../include/graphqlcpp/exceptions/NoSchemaSetException.h"
#include "../../include/graphqlcpp/exceptions/InvalidSchemaException.h"

namespace graphqlcpp {
namespace api {
using namespace facebook::graphql;
using namespace graphqlcpp::exceptions;

GraphqlCppApi::GraphqlCppApi() {
	this->schemaValidator = new SchemaValidator();
}

void GraphqlCppApi::setSchema(const char* schema) {
	auto rootNode = parseSchemaStringToSchemaAst(schema);
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

	Node* GraphqlCppApi::parseSchemaStringToSchemaAst(const char* schema) {
		//TODO check error string
		const char* err = "";
		std::unique_ptr<Node> schemaAst;
		schemaAst = parseStringWithExperimentalSchemaSupport(schema, &err);
		Node* rootNode = schemaAst.get();
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

