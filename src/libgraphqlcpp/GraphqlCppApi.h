/*
 * GraphqlCppApi.h
 *
 *  Created on: 10.02.2019
 *      Author: admin
 */

#ifndef GRAPHQLCPPAPI_H_
#define GRAPHQLCPPAPI_H_

#include "../libgraphqlparser/Ast.h"
#include "validators/SchemaValidator.h"
#include "validators/QueryValidator.h"
#include "exceptions/NoSchemaSetException.h"
#include "exceptions/InvalidSchemaException.h"

namespace graphqlcpp {
namespace api {
using namespace facebook::graphql::ast;
using namespace validators;
using namespace graphqlcpp::exceptions;

class GraphqlCppApi {
private:
	SchemaAstWraper* schemaWraper = nullptr;
	SchemaValidator* schemaValidator = nullptr;
	QueryValidator* queryValidator = nullptr;

public:
	GraphqlCppApi();
	~GraphqlCppApi();
	void setSchema(const char* schema);
	const char* printSchemaAsJson();
	const char* executeQuery(const char* query);

private:
	bool checkIfRequestValid(Node* rootNodeRequest);
	Node* parseStringToAst(const char* str);
};

} /* namespace graphqlcppapi */
}
#endif /* GRAPHQLCPPAPI_H_ */
