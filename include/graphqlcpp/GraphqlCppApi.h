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
            SchemaAstWraper *schemaWrapper = nullptr;
            SchemaValidator *schemaValidator = nullptr;
            QueryValidator *queryValidator = nullptr;
            ResolverManager *resolverManager = nullptr;
            RequestDispatcher *requestDispatcher = nullptr;
            std::string introspectionSchema = "";

            /**
             * The constructor of the GraphqlCpp Class. The Ctor is private. This class should be created
             * via the Factory Method.
             */
            GraphqlCppApi();

            /***
             * This method checks whether a request is valid or not
             * @param rootNodeRequest the root node of the query ast (abstract syntax tree)
             * @return true if the request is valid otherwise it returns false
             */
            bool checkIfRequestValid(Node *rootNodeRequest);

            /***
             * This functions converts a request string to an ast using the facebook graphqlparser library
             * @param str the string to parse
             * @return the root node of the ast
             */
            Node *parseStringToAst(const std::string &str);

            /***
             * This functions converts a schema string to ast using the facebook graphqlparser library
             * @param str the schema string to parse
             * @return the root node of the schema ast
             */
            Node *parseSchemaStringToSchemaAst(const std::string &str);

        public:
            /***
             * Dstructor
             */
            ~GraphqlCppApi();

            /**
             * This function function is used to register the graphql schema. The schema must match with your DTOs and
             * the resolvers you register. You need to register a schema before you can use this library. Check out
             * the IntegrationTests to find some examples
             * @param schema
             */
            void setSchema(const std::string &schema);

            /**
             * Use this method to register your graphql introspection schema. This is needed for type introspection
             * with graphiql. If you don't use graphiql you don't need this.
             * @param introspectionSchema the string with the introspection schema.
             */
            void setGraphiQlIntrospectionSchema(std::string introspectionSchema);

            /**
             * Returns the graphiql introspection schema
             * @return the introspection schema
             */
            std::string getGraphiQlIntrospectionSchema();

            /**
             * Here you need to register your resolvers before you can use this library. The resolver must match the
             * registered schema. Checkout the IntegrationTests to find an example.
             * @param the resolver is called if its requested in the request
             */
            void registerResolver(IGraphQlResolver *resolver);

            /**
             * Call this method to execute a graphql request. Before you need to set a schema an register the matching
             * resolvers.
             * @param the graphql request
             * @return the graphql response
             */
            string executeRequest(const std::string &request);

            /**
             * Only for debugging. Returns the registered schema as Json
             * @return the registerd schema as json
             */
            const char *printSchemaAsJson();

            /***
             * Factory method for GraphQlCppApi
             * @return a new instance of this class
             */
            static GraphqlCppApi *createInstance();
        };

    } /* namespace graphqlcppapi */
}
#endif /* GRAPHQLCPPAPI_H_ */
