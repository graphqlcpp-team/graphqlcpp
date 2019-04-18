//
// Created by amelie on 16.04.19.
//

#ifndef GRAPHQLCPP_QUERYWRAPPER_H
#define GRAPHQLCPP_QUERYWRAPPER_H

#include <vector>
#include "string"
#include "resolver/ResolverInfo.h"
#include "../graphqlparser/AstNode.h"
#include "../graphqlparser/Ast.h"

namespace graphqlcpp {

    class RequestAstWrapper {
    private:
        facebook::graphql::ast::Node* queryRootNode;

        const char *getOperation(facebook::graphql::ast::Node *rootNodeQuery);
    public:
        RequestAstWrapper(facebook::graphql::ast::Node *queryRootNode);

        ResolverInfo* extractResolver();
        std::string extractOperation();
        facebook::graphql::ast::SelectionSet* extractSelectionSetForSerialisation();
    };

}
#endif //GRAPHQLCPP_QUERYWRAPPER_H
