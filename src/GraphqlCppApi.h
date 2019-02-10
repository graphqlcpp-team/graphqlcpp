/*
 * GraphqlCppApi.h
 *
 *  Created on: 10.02.2019
 *      Author: admin
 */

#ifndef GRAPHQLCPPAPI_H_
#define GRAPHQLCPPAPI_H_

#include "libgraphqlparser/Ast.h"
#include "SchemaValidator.h"

namespace graphqlcpp {
namespace api {
using namespace facebook::graphql::ast;
using namespace validators;

class GraphqlCppApi {
private:
	int test;
	Node* schemaAst;
	SchemaValidator* schemaValidator;

public:
	GraphqlCppApi();
	void setSchema(const char* schema);
	const char* printSchemaAsJson();
	bool checkIfRequestValid(const char* request);
};

} /* namespace graphqlcppapi */
}
#endif /* GRAPHQLCPPAPI_H_ */
