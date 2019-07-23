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
#include "../../include/graphqlcpp/exceptions/InvalidRequestException.h"
#include "../../include/graphqlcpp/resolver/IGraphQlResolver.h"
#include "../../include/graphqlcpp/resolver/ResolverManager.h"
#include "../../include/graphqlcpp/RequestAstWrapper.h"

namespace graphqlcpp {
    namespace api {
        using namespace facebook::graphql;
        using namespace graphqlcpp::exceptions;
        using namespace graphqlcpp::resolver;

        GraphqlCppApi::GraphqlCppApi() {
            this->schemaValidator = new SchemaValidator();
            this->resolverManager = new ResolverManager();
            this->requestDispatcher = new RequestDispatcher(resolverManager);
        }

        void GraphqlCppApi::setSchema(const std::string &schema) {
            auto rootNode = parseSchemaStringToSchemaAst(schema);
            if (schemaValidator->checkIfSchemaIsValid(rootNode)) {
                schemaWrapper = new SchemaAstWraper(rootNode);
                queryValidator = new QueryValidator(schemaWrapper);
            } else {
                throw InvalidSchemaException();
            }
        }

        bool GraphqlCppApi::checkIfRequestValid(Node *rootNodeRequest) {
            if (queryValidator != nullptr) {
                return this->queryValidator->isQueryValid(rootNodeRequest);
            }
            throw NoSchemaSetException();
        }

        string GraphqlCppApi::executeRequest(const std::string &request) {
            Node *requestAst = parseStringToAst(request);
            if (checkIfRequestValid(requestAst)) {
                graphqlcpp::RequestAstWrapper* requestWrapper = new graphqlcpp::RequestAstWrapper(requestAst);
                std::string response = this->requestDispatcher->executeRequest(requestWrapper);
                delete requestWrapper;
                return response;
            }
            throw exceptions::InvalidRequestException();
        }

        Node *GraphqlCppApi::parseStringToAst(const std::string &str) {
            const char *error = nullptr;
            std::unique_ptr<Node> queryAst;
            queryAst = parseString(str.c_str(), &error);
            if(error!= nullptr){
                throw exceptions::InvalidRequestException();
            }
            Node *rootNode = queryAst.release();
            return rootNode;
        }

        Node *GraphqlCppApi::parseSchemaStringToSchemaAst(const std::string &schema) {
            const char *err = nullptr;
            std::unique_ptr<Node> schemaAst;
            std::string mystr = schema;
            schemaAst = parseStringWithExperimentalSchemaSupport(mystr.c_str(), &err);
            Node *rootNode = schemaAst.release();
            if(err!= nullptr){
                throw exceptions::InvalidSchemaException();
            }
            return rootNode;
        }


        const char *GraphqlCppApi::printSchemaAsJson() {
            if (schemaWrapper != nullptr) {
                return schemaWrapper->printSchemaAsJson();
            }
            throw NoSchemaSetException();
        }

        GraphqlCppApi::~GraphqlCppApi() {
            delete schemaWrapper;
            delete schemaValidator;
            delete queryValidator;
            delete resolverManager;
            delete requestDispatcher;
        }

        void GraphqlCppApi::registerResolver(IGraphQlResolver *resolver) {
            this->resolverManager->registerResolver(resolver);
        }

        void GraphqlCppApi::setGraphiQlIntrospectionSchema(std::string introspectionSchema) {
            this->introspectionSchema = introspectionSchema;
        }

        std::string GraphqlCppApi::getGraphiQlIntrospectionSchema() {
            return this->introspectionSchema;
        }

        GraphqlCppApi *GraphqlCppApi::createInstance() {
            return new GraphqlCppApi();
        }
    }
} /* namespace graphqlcppapi */

