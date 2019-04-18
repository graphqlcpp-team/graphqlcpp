//
// Created by amelie on 16.04.19.
//

#include "../../include/graphqlcpp/RequestAstWrapper.h"

#include "../../../include/graphqlcpp/validators/QueryValidator.h"
#include "../../graphqlparser/c/GraphQLAst.h"
#include "../../../include/graphqlparser/Ast.h"
#include "../../../include/graphqlcpp/exceptions/InvalidQueryException.h"
#include "../../../include/graphqlcpp/exceptions/WrongOperationException.h"

namespace graphqlcpp {
    using namespace graphqlcpp::exceptions;

    using namespace facebook::graphql;
    using namespace facebook::graphql::ast;

    //TODO aufräumen new

    graphqlcpp::RequestAstWrapper::RequestAstWrapper(facebook::graphql::ast::Node *queryRootNode) {
        this->queryRootNode = queryRootNode;
    }

    graphqlcpp::ResolverInfo *graphqlcpp::RequestAstWrapper::extractResolver() {
        auto selectionSet = extractSelectionSetForSerialisation();
        std::string name;
        if (selectionSet == nullptr) {
            //TODO throw exception
            return nullptr;
        }
        name = std::string(getNameOfSelectionSet(selectionSet));
        return new ResolverInfo(name, getArgumentsOfSelectionSet(selectionSet));
    }



    std::string graphqlcpp::RequestAstWrapper::extractOperation() {
        return std::string(getOperation(queryRootNode));
    }

    const SelectionSet *graphqlcpp::RequestAstWrapper::extractSelectionSetForSerialisation() {
        const auto &selection = getSelectionSet(this->queryRootNode)->getSelections().at(0);
        //get the pointer to the field on place index in the list/array of Selections.
        // The field is a node of the AST.
        const GraphQLAstField *graphQlField =
                (GraphQLAstField *) selection.get();
        auto field = (const Field *) graphQlField;
        return field->getSelectionSet();
    }

    //URL: https://stackoverflow.com/questions/29049584/heap-corruption-trying-to-add-elements-to-existing-stdvector

    std::vector<ResolverArgument*> *RequestAstWrapper::getArgumentsOfSelectionSet(const SelectionSet* selectionSet) {
        std::vector<ResolverArgument*> *vectorResolverArguments = new std::vector<ResolverArgument*>();

        const auto &selection = selectionSet->getSelections().at(0);
        //get the pointer to the field on place index in the list/array of Selections.
        // The field is a node of the AST.
        const GraphQLAstField *graphQlField =
                (GraphQLAstField *) selection.get();
        auto field = (const Field *) graphQlField;
        auto arguments = field->getArguments();
        for(const auto &argument : *arguments) {
            vectorResolverArguments->push_back(generateResolverArgument(argument));
        }
        return vectorResolverArguments;
    }

    ResolverArgument* RequestAstWrapper::generateResolverArgument(const unique_ptr <Argument> & argument) {
        const char* name = argument->getName().getValue();
        const Value* value = &argument->getValue();

        const StringValue *booleanValue = (StringValue *) value;
        const char *argumentsValue = booleanValue->getValue();
        std::string args;
        if( ((int *) &argumentsValue[0]) == (int *) 0x1) {
            args = "true";
        }
        else if(((int *) &argumentsValue[0]) == (int *)nullptr) {
            args = "false";
        }
        else {
            args = argumentsValue;
        }

        ResolverArgument* resolverArgument = new ResolverArgument(name, args);
        return  resolverArgument;
    }

    const char *graphqlcpp::RequestAstWrapper::getNameOfSelectionSet(const SelectionSet *selectionSet) {
        //getSelections return a vector pointers to Selections. The vector can
        // be seen as an array, over which we will iterate. Over the index we
        // can access all Selections.
        const auto &selection = selectionSet->getSelections().at(0);

        //get the pointer to the field on place index in the list/array of Selections.
        // The field is a node of the AST.
        const GraphQLAstField *graphQlField =
                (GraphQLAstField *) selection.get();
        auto field = (const Field *) graphQlField;

        const Name *namePointer = &field->getName();
        const char *name = namePointer->getValue();

        return name;
    }

    /**
     * This method gets the operation of the query.
     * @param rootNodeQuery The root node of the query AST.
     * @return The operation.
     */
    const char *graphqlcpp::RequestAstWrapper::getOperation(facebook::graphql::ast::Node *rootNodeQuery) {
        const OperationDefinition *operationDefinition = getOperationDefinition(rootNodeQuery);
        const char *operation = operationDefinition->getOperation();
        return operation;
    }

    /**
         * This method gets the selection set of the root node.
         * Only the root note is of type node. Afterwards the nodes are of type selection set.
         * @param rootNodeQuery The root node of the query AST.
         * @return The selection set of the root node.
         */
    const SelectionSet *RequestAstWrapper::getSelectionSet(Node *rootNodeQuery) {
        const OperationDefinition *operationDefinition = getOperationDefinition(
                rootNodeQuery);
        auto graphQlSelectionSet =
                (const struct GraphQLAstSelectionSet *) &operationDefinition->getSelectionSet();
        const auto *selectionSet =
                (const SelectionSet *) graphQlSelectionSet;
        return selectionSet;
    }

    /**
     * This method gets the operation definition.
     * Out of the operation definition the operation can be extracted. Also the selection set of the root node
     * is located in the operation definition.
     * In both ways the operation definition must be determined.
     * @param rootNodeQuery The root node of the query AST.
     * @return The operation definition.
     */
    const OperationDefinition *RequestAstWrapper::getOperationDefinition(
            Node *rootNodeQuery) {
        const auto *graphQlAstDocument =
                (const struct GraphQLAstDocument *) rootNodeQuery;
        const auto *realNode = (const Document *) graphQlAstDocument;
        const std::vector<std::unique_ptr<Definition>> &definition =
                realNode->getDefinitions();
        std::unique_ptr<Definition, default_delete<Definition>>::pointer operationDefinitionNotCasted =
                definition[0].get();
        const auto *operationDefinitionCasted =
                (const GraphQLAstOperationDefinition *) operationDefinitionNotCasted;
        const auto *operationDefinition =
                (const OperationDefinition *) operationDefinitionCasted;
        return operationDefinition;
    }

}
