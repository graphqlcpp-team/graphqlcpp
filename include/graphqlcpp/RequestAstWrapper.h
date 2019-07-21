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

    using namespace facebook::graphql::ast;

    class RequestAstWrapper {
    private:
        facebook::graphql::ast::Node* queryRootNode;

        const char *getOperation(Node *rootNodeQuery);
        const OperationDefinition *getOperationDefinition(Node *rootNodeQuery);
        const SelectionSet *getSelectionSet(Node *rootNodeQuery);
        const char* getNameOfSelectionSet(const SelectionSet *selectionSet);
        std::vector<ResolverArgument*> *getArgumentsOfSelectionSet(const SelectionSet* selectionSet);
        ResolverArgument* generateResolverArgument(const std::unique_ptr <Argument> &);
    public:
        RequestAstWrapper(facebook::graphql::ast::Node *queryRootNode);

        ResolverInfo extractResolver();
        std::string extractOperation();
        const SelectionSet* extractSelectionSetForSerialisation();
    };

}
#endif //GRAPHQLCPP_QUERYWRAPPER_H
