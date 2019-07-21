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
    /**
     * The constructor of the GraphqlCpp Class
     */
	GraphqlCppApi();
	bool checkIfRequestValid(Node* rootNodeRequest);
	Node* parseStringToAst(const std::string &str);
	Node* parseSchemaStringToSchemaAst(const std::string &str);

public:
	~GraphqlCppApi();

	/**
	 *
	 * @param schema
	 */
	void setSchema(const std::string &schema);
    void setGraphiQlIntrospectionSchema(std::string introspectionSchema);
    std::string getGraphiQlIntrospectionSchema();
	void registerResolver(IGraphQlResolver* resolver);
    string executeRequest(const std::string &request);

    const char * printSchemaAsJson();

    /***
     * Factory method for GraphQlCppApi
     * @return
     */
    static GraphqlCppApi* createInstance();
};

} /* namespace graphqlcppapi */
}
#endif /* GRAPHQLCPPAPI_H_ */
