//
// Created by julian on 13.04.19.
//

#include "../../../include/graphqlcpp/dispatcher/RequestDispatcher.h"


graphqlcpp::api::IGraphQlDTO *
graphqlcpp::dispatcher::RequestDispatcher::executeRequest(facebook::graphql::ast::Node *requestAst) {
    auto requestType = getRequestType(requestAst);
    if(requestType == "query"){

    }
}

graphqlcpp::dispatcher::RequestDispatcher::RequestDispatcher(graphqlcpp::resolver::ResolverManager *resolverManager,
                                                             graphqlcpp::validators::SchemaAstWraper *schemaAstWraper) {
    this->schemaAstWraper = schemaAstWraper;
    this->resolverManager = resolverManager;

}

std::string graphqlcpp::dispatcher::RequestDispatcher::getRequestType(facebook::graphql::ast::Node *requestAst) {
    return "query";
}
