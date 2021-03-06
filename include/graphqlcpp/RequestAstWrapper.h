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
        std::vector<ResolverArgument> getArgumentsOfSelectionSet(const SelectionSet* selectionSet);

        /**
         * This function will generate a resolver argument object.
         * The name and the value of an argument will be extracted. These are part of the resolver argument object.
         * @return An instance of a resolverArgument object.
         */
        ResolverArgument generateResolverArgument(const std::unique_ptr <Argument> &);
    public:
        /**
         * C'stor.
         * This wraps all operation with the queryAst.
         * @param queryRootNode The root node of the query AST.
         */
        RequestAstWrapper(facebook::graphql::ast::Node *queryRootNode);

        /**
         * This function extracts the resolverInfo. The resolve Info is consisting of the resolver name and arguments.
         * The resolver name is the name of the selectionSet of the rootNodeQuery.
         * The resolver arguments are ResolverArguments. These are consisting of the name and the value. These are
         * extracted out of the arguments of the selectionSet of the rootNodeQuery.
         * @return
         */
        ResolverInfo extractResolver();

        /**
         * This function will extract the operation of the request.
         * @return The operation (query, mutation or subscription).
         */
        std::string extractOperation();

        /**
         * This function will return the selection set one level under the root level selection set.
         * This is used to iterate through the query AST.
         * @return
         */
        const SelectionSet* extractSelectionSetForSerialisation();
    };

}
#endif //GRAPHQLCPP_QUERYWRAPPER_H
