//
// Created by amelie on 16.04.19.
//

#include "../../include/graphqlcpp/RequestAstWrapper.h"

graphqlcpp::RequestAstWrapper::RequestAstWrapper(facebook::graphql::ast::Node *queryRootNode) : queryRootNode(
        queryRootNode) {}
