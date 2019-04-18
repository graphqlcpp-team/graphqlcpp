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
#include "../../include/graphqlcpp/resolver/IGraphQlResolver.h"
#include "../../include/graphqlcpp/resolver/ResolverManager.h"

namespace graphqlcpp {
    namespace api {
        using namespace facebook::graphql;
        using namespace graphqlcpp::exceptions;
        using namespace graphqlcpp::resolver;

        GraphqlCppApi::GraphqlCppApi() {
            this->schemaValidator = new SchemaValidator();
            this->resolverManager = new ResolverManager();
        }

        void GraphqlCppApi::setSchema(const char *schema) {
            auto rootNode = parseSchemaStringToSchemaAst(schema);
            if (schemaValidator->checkIfSchemaIsValid(rootNode)) {
                schemaWraper = new SchemaAstWraper(rootNode);
                queryValidator = new QueryValidator(schemaWraper);
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

        const char *GraphqlCppApi::executeQuery(const char *query) {
            Node *requestAst = parseStringToAst(query);
            if (checkIfRequestValid(requestAst)) {
                return schemaWraper->printSchemaAsJson();
            }
            return "query was invalid";
        }

        Node *GraphqlCppApi::parseStringToAst(const char *str) {
            //TODO check error string
            const char *error = nullptr;
            std::unique_ptr<Node> queryAst;
            queryAst = parseString(str, &error);
            //const char* err = "";
            //auto sAst = parseString(str, &err);
            Node *rootNode = queryAst.release();
            return rootNode;
        }

        Node *GraphqlCppApi::parseSchemaStringToSchemaAst(const char *schema) {
            //TODO check error string
            const char *err = "";
            std::unique_ptr<Node> schemaAst;
            schemaAst = parseStringWithExperimentalSchemaSupport(schema, &err);
            Node *rootNode = schemaAst.release();
            return rootNode;
        }


        const char *GraphqlCppApi::printSchemaAsJson() {
            if (schemaWraper != nullptr) {
                return schemaWraper->printSchemaAsJson();
            }
            throw NoSchemaSetException();
        }

        GraphqlCppApi::~GraphqlCppApi() {
            delete schemaWraper;
            delete schemaValidator;
            delete queryValidator;
            delete resolverManager;
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
    }
} /* namespace graphqlcppapi */

