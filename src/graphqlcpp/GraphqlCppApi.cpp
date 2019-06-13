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
#include "../../include/graphqlcpp/RequestAstWrapper.h"
#include <string>
#include <cstring>

namespace graphqlcpp {
    namespace api {
        using namespace facebook::graphql;
        using namespace graphqlcpp::exceptions;
        using namespace graphqlcpp::resolver;

        //TODO place this function in string utils class
        char* toCharArr(const std::string & str){
            char char_array[str.length() + 1];

            // copying the contents of the
            // string to char array
            std::strcpy(char_array, str.c_str());
            return char_array;
        }

        GraphqlCppApi::GraphqlCppApi() {
            this->schemaValidator = new SchemaValidator();
            this->resolverManager = new ResolverManager();
            this->requestDispatcher = new RequestDispatcher(resolverManager);
        }

        void GraphqlCppApi::setSchema(const std::string &schema) {
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


        string GraphqlCppApi::executeRequest(const std::string &request) {
            Node *requestAst = parseStringToAst(request);
            if (checkIfRequestValid(requestAst)) {
                graphqlcpp::RequestAstWrapper* requestWrapper = new graphqlcpp::RequestAstWrapper(requestAst);
                std::string response = this->requestDispatcher->executeRequest(requestWrapper);
                return response.c_str();
            }
            return "request was invalid";
        }

        Node *GraphqlCppApi::parseStringToAst(const std::string &str) {
            //TODO check error string
            const char *error = nullptr;
            std::unique_ptr<Node> queryAst;
            queryAst = parseString(toCharArr(str), &error);
            //const char* err = "";
            //auto sAst = parseString(str, &err);
            Node *rootNode = queryAst.release();
            return rootNode;
        }

        Node *GraphqlCppApi::parseSchemaStringToSchemaAst(const std::string &schema) {
            //TODO check error string
            const char *err = "";
            std::unique_ptr<Node> schemaAst;
            schemaAst = parseStringWithExperimentalSchemaSupport(toCharArr(schema), &err);
            Node *rootNode = schemaAst.release();
            return rootNode;
        }


//        const char *GraphqlCppApi::printSchemaAsJson() {
//            if (schemaWraper != nullptr) {
//                return schemaWraper->printSchemaAsJson();
//            }
//            throw NoSchemaSetException();
//        }

        GraphqlCppApi::~GraphqlCppApi() {
            delete schemaWraper;
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
    }
} /* namespace graphqlcppapi */

