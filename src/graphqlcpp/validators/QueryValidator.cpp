/*
 * QueryValidator.cpp
 *
 *  Created on: 17.02.2019
 *      Author: amelie
 */

#include "../../../include/graphqlcpp/validators/QueryValidator.h"
#include "../../graphqlparser/c/GraphQLAst.h"
#include "../../../include/graphqlparser/Ast.h"
#include "../../../include/graphqlcpp/exceptions/InvalidQueryException.h"
#include "../../../include/graphqlcpp/exceptions/WrongOperationException.h"
#include <vector>
#include <memory>
#include <cstring>

namespace graphqlcpp {
    namespace validators {

        using namespace graphqlcpp::exceptions;
        using namespace std;
        using namespace facebook::graphql;
        using namespace facebook::graphql::ast;

        /**
         * Constructor of the query validator class.
         * Needs an object of the schemaAstWrapper because the validation query vs schema will be done by the
         * schemaAstWrapper. The schemaAstWrapper contains the schema AST for this specific query.
         * @param schemaWrapper An object of the schemaAstWrapper.
         */
        QueryValidator::QueryValidator(SchemaAstWraper *schemaWrapper) {
            this->schemaWrapper = schemaWrapper;
        }

        /**
         * This method checks if a query is valid.
         * Checks if the operation of the query is a valid operation given in the schema.
         * Every node of the query (element of the query) will be validate against the schema.
         * It will check if a node of the query exists under the same father element as in the schema.
         * Every argument of the query will be validate against the schema.
         * This is TODO
         * @param rootNodeQuery The root node of the query AST.
         * @return True, if the query is valid, otherwise false.
         * @throw InvalidQueryExceprion if the query is not valid.
         * @throw WrongOperationException if the operation is not set in the schema.
         */
        bool QueryValidator::isQueryValid(Node *rootNodeQuery) {
            const char *operation = getOperation(rootNodeQuery);
            if (!this->schemaWrapper->isOperationValid(operation)) {
                throw WrongOperationException();
            }
            const SelectionSet *selectionSet = getSelectionSet(rootNodeQuery);
            char nullChar = '\0';
            if (!iterateThroughSelectionSetsAndValidate(selectionSet, operation)) {
                throw InvalidQueryException();
                return false;
            }

            return true;
        }


        /**
         * This method will iterate through a selection set an validate every selection set which is a child.
         * A selection set is a node of the AST. The selection set is an array of all nodes which are located under
         * a node. It can be iterate over every element. This element contains the name and the arguments.
         * This method will validate if the name of this element exists as a child of the father element in the
         * schema AST. Therefore the name of the father node is a transfer parameter.
         * If the node exists as a child of the father, every argument will be validate.
         * If the arguments are valid, the method will call itself recursivly to validate the whole AST.
         * The method walks through the AST in preorder.
         * @param selectionSet The selection set which conna be validate.
         * @param fatherFieldName The name of the father node element.
         * @return True, if the two validation steps were successfull, otherwise false.
         */
        bool QueryValidator::iterateThroughSelectionSetsAndValidate(
                const SelectionSet *selectionSet, const char *fatherFieldName) {

            //exit condition: if there is no SelectionSet exit the recursion
            // The selectionSet is the access to the next level of the AST
            if (selectionSet != nullptr) {

                //getSelections return a vector pointers to Selections. The vector can
                // be seen as an array, over which we will iterate. Over the index we
                // can access all Selections.
                const std::vector<std::unique_ptr<Selection>> &selections =
                        selectionSet->getSelections();

                //a separate counter variable because the counter variable i of the for-loop is of type pointer.
                for (const auto &selection : selections) {

                    //get the pointer to the field on place index in the list/array of Selections.
                    // The field is a node of the AST.
                    const GraphQLAstField *graphQlField =
                            (GraphQLAstField *) selection.get();
                    auto field = (const Field *) graphQlField;
                    this->schemaWrapper->validateNode(fatherFieldName, field);
                    const Name *namePointer = &field->getName();
                    const char *name = namePointer->getValue();

                    //call method which will validate if the node exists as child of the father node.
                    //iterate through all arguments of the node and validate them
                    if (!this->schemaWrapper->validateNode(fatherFieldName, field)) {
                        return false;
                    }

                    //get the next level of the AST, this means get the SelectionSet of this level
                    const SelectionSet *selectionSetOfField = field->getSelectionSet();

                    //iterate through the next level recursive and validate each node.
                    if (!iterateThroughSelectionSetsAndValidate(selectionSetOfField,
                                                                name)) {
                        return false;
                    }
                }
            }
            return true;
        }

        /** bool QueryValidator::iterateThroughArgumentsOfOneFiledAndValidate(
         * This method iterates through all arguments of a field and validates these.
         * For every argument the name and the value are validate against the schema AST.
         * There are different kinds of values which can be arguments. The differentiation must be done by the
         * schemaAstWrapper. That's because in the schema the expected type of value is specified. It can be checked
         * if it is possible to cast the value to the expected type of value.
         * @param field The field of which the arguments should be validated.
         * @return True, if no arguments are there or if the arguments are valid. Otherwise false.
         */

        /**
         * This method gets the operation of the query.
         * @param rootNodeQuery The root node of the query AST.
         * @return The operation.
         */
        const char *QueryValidator::getOperation(Node *rootNodeQuery) {
            const OperationDefinition *operationDefinition = getOperationDefinition(
                    rootNodeQuery);
            const char *operation = operationDefinition->getOperation();
            return operation;
        }

        /**
         * This method gets the selection set of the root node.
         * Only the root note is of type node. Afterwards the nodes are of type selection set.
         * @param rootNodeQuery The root node of the query AST.
         * @return The selection set of the root node.
         */
        const SelectionSet *QueryValidator::getSelectionSet(Node *rootNodeQuery) {
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
        const OperationDefinition *QueryValidator::getOperationDefinition(
                Node *rootNodeQuery) {
            const auto *graphQlAstDocument =
                    (const struct GraphQLAstDocument *) rootNodeQuery;
            const auto *realNode = (const Document *) graphQlAstDocument;
            const std::vector<std::unique_ptr<Definition>> &definition =
                    realNode->getDefinitions();
            std::unique_ptr<Definition, default_delete<Definition>>::pointer operationDefinitioNotCasted =
                    definition[0].get();
            const auto *operationDefinitionCasted =
                    (const GraphQLAstOperationDefinition *) operationDefinitioNotCasted;
            const auto *operationDefinition =
                    (const OperationDefinition *) operationDefinitionCasted;
            return operationDefinition;
        }
    }
}
