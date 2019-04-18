/*
 * GraphqlCppApi.h
 *
 *  Created on: 10.02.2019
 *      Author: admin
 */

#ifndef GRAPHQLCPPAPI_H_
#define GRAPHQLCPPAPI_H_

#include "exceptions/NoSchemaSetException.h"
#include "exceptions/InvalidSchemaException.h"
#include "validators/QueryValidator.h"
#include "validators/SchemaValidator.h"
#include "validators/SchemaAstWraper.h"
#include "../graphqlparser/Ast.h"
#include "resolver/IGraphQlResolver.h"
#include "resolver/ResolverManager.h"
#include <string>

#include "dispatcher/RequestDispatcher.h"
#include "RequestAstWrapper.h"

namespace graphqlcpp {
namespace api {
using namespace facebook::graphql::ast;
using namespace validators;
using namespace graphqlcpp::exceptions;
using namespace resolver;
using namespace dispatcher;


class GraphqlCppApi {
private:
	SchemaAstWraper* schemaWraper = nullptr;
	SchemaValidator* schemaValidator = nullptr;
	QueryValidator* queryValidator = nullptr;
	ResolverManager* resolverManager = nullptr;
	RequestDispatcher* requestDispatcher = nullptr;
    std::string introspectionSchema = "";

public:
	GraphqlCppApi();
	~GraphqlCppApi();
	void setSchema(const char* schema);

    void setGraphiQlIntrospectionSchema(std::string introspectionSchema);

    std::string getGraphiQlIntrospectionSchema();
	void registerResolver(IGraphQlResolver* resolver);
	const char* printSchemaAsJson();

    const char *executeRequest(const char *request);

private:
	bool checkIfRequestValid(Node* rootNodeRequest);
	Node* parseStringToAst(const char* str);
	Node* parseSchemaStringToSchemaAst(const char* str);
};

} /* namespace graphqlcppapi */
}
#endif /* GRAPHQLCPPAPI_H_ */
