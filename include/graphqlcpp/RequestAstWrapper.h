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
        /**
         * To execute operations with the query AST we need the query AST root node.
         */
        facebook::graphql::ast::Node* queryRootNode;

        /**
         * This function will return the operation of the query.
         * @param rootNodeQuery The root node of the query AST.
         * @return The operation of the query.
         */
        const char *getOperation(Node *rootNodeQuery);

        /**
         * This function will return the operationDefinition. Helper function for getOperation and getSelectionSet.
         * @param rootNodeQuery The root node of the query AST.
         * @return The operation definition.
         */
        const OperationDefinition *getOperationDefinition(Node *rootNodeQuery);

        /**
         * This function will return the selectionSet. The selection set is used to iterate over the query AST.
         * @param rootNodeQuery The root node of the query AST.
         * @return The selectionSet.
         */
        const SelectionSet *getSelectionSet(Node *rootNodeQuery);

        /**
         * This function will get the name of the selection set. The name is the field which is requested.
         * This means it is the name of the resolver function.
         * @param selectionSet The selection set to which the name should be extracted.
         * @return The name of the selection set.
         */
        const char* getNameOfSelectionSet(const SelectionSet *selectionSet);

        /**
         * This function will get the arguments of a selection set.
         * The arguments are passed to the resolver function.
         * @param selectionSet The selection set, which arguments should be extracted.
         * @return An array of arguments.
         */
        std::vector<ResolverArgument*> *getArgumentsOfSelectionSet(const SelectionSet* selectionSet);

        /**
         *
         * @return
         */
        ResolverArgument* generateResolverArgument(const std::unique_ptr <Argument> &);
    public:
        RequestAstWrapper(facebook::graphql::ast::Node *queryRootNode);

        ResolverInfo extractResolver();
        std::string extractOperation();
        const SelectionSet* extractSelectionSetForSerialisation();
    };

}
#endif //GRAPHQLCPP_QUERYWRAPPER_H
