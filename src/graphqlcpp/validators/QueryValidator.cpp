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
            if(!this->schemaWrapper->isOperationValid(operation)) {
                throw WrongOperationException();
            }
            const SelectionSet *selectionSet = getSelectionSet(rootNodeQuery);
            char nullChar = '\0';
            //const char *firstElement = &nullChar;
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
            if (selectionSet != 0x0) {

                //getSelections return a vector pointers to Selections. The vector can
                // be seen as an array, over which we will iterate. Over the index we
                // can access all Selections.
                const std::vector<std::unique_ptr<Selection>> &selectionSetArray =
                        selectionSet->getSelections();

                //a separate counter variable because the counter variable i of the for-loop is of type pointer.
                int index = 0;
                for (auto i = selectionSetArray.begin(); i != selectionSetArray.end();
                     ++i) {

                    //get the pointer to the field on place index in the list/array of Selections.
                    // The field is a node of the AST.
                    const GraphQLAstField *graphQlField =
                            (GraphQLAstField *) selectionSetArray[index].get();
                    const Field *field = (const Field *) graphQlField;
                    const Name *namePointer = &field->getName();
                    const char *name = namePointer->getValue();

                    int countArguments = getCountOfArguments(field);

                    //call method which will validate if the node exists as child of the father node.
                    if (!this->schemaWrapper->nodeExistsAsChildOf(name,
                                                                    fatherFieldName, countArguments)) {
                        return false;
                    }

                    //iterate thorugh all arguments of the node and validate them
                    if (!iterateThroughArgumentsOfOneFiledAndValidate(field)) {
                        return false;
                    }

                    //get the next level of the AST, this means get the SelectionSet of this level
                    const SelectionSet *selectionSetOfField = field->getSelectionSet();

                    //iterate through the next level recursive and validate each node.
                    if (!iterateThroughSelectionSetsAndValidate(selectionSetOfField,
                                                                name)) {
                        return false;
                    }
                    index++;
                }
            }
            return true;
        }

        int QueryValidator::getCountOfArguments(const Field *field) {
            const std::vector<std::unique_ptr<Argument>> *argumentPointer =
                    field->getArguments();

            //if there is no argument exit function with true
            if (argumentPointer == 0x0) {
                return 0;
            }
            const std::vector<std::unique_ptr<Argument>> &argumentArray =
                    *argumentPointer;
            return static_cast<int>(argumentArray.size());
        }

        /**
         * This method iterates through all arguments of a field and validates these.
         * For every argument the name and the value are validate against the schema AST.
         * There are different kinds of values which can be arguments. The differentiation must be done by the
         * schemaAstWrapper. That's because in the schema the expected type of value is specified. It can be checked
         * if it is possible to cast the value to the expected type of value.
         * @param field The field of which the arguments should be validated.
         * @return True, if no arguments are there or if the arguments are valid. Otherwise false.
         */
        bool QueryValidator::iterateThroughArgumentsOfOneFiledAndValidate(
                const Field *field) {

            //getArguments return a Pointer. Will need the value of this address to get one argument
            // from the list of arguments.
            const std::vector<std::unique_ptr<Argument>> *argumentPointer =
                    field->getArguments();

            //if there is no argument exit function with true
            if (argumentPointer == 0x0) {
                return true;
            }
            const std::vector<std::unique_ptr<Argument>> &argumentArray =
                    *argumentPointer;

            //a separate counter variable because the counter variable j of the for-loop is of type pointer.
            int index = 0;
            for (auto j = argumentArray.begin(); j != argumentArray.end(); ++j) {

                //pointer to the argument on place index in the list/array of arguments
                std::unique_ptr<Argument, default_delete<Argument>>::pointer argumentPointerOneField =
                        argumentArray[index].get();
                const GraphQLAstArgument *graphQLAstArgument =
                        (GraphQLAstArgument *) argumentPointerOneField;
                const Argument *argument = (const Argument *) graphQLAstArgument;

                const Name *nameA = &argument->getName();
                const char *nameAr = nameA->getValue();
                const Value &valueA = argument->getValue();
                const Value *pointerA = &valueA;
                if(!this->schemaWrapper->isArgumentValid(nameAr, pointerA, field->getName().getValue())) {
                    return false;
                }
                //call method to validate the argument

                cout << "Name Argument: " << nameAr << endl;

                index++;
            }
            return true;
        }

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
            const GraphQLAstSelectionSet *graphQlSelectionSet =
                    (const struct GraphQLAstSelectionSet *) &operationDefinition->getSelectionSet();
            const SelectionSet *selectionSet =
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
            const GraphQLAstDocument *graphQlAstDocument =
                    (const struct GraphQLAstDocument *) rootNodeQuery;
            const Document *realNode = (const Document *) graphQlAstDocument;
            const std::vector<std::unique_ptr<Definition>> &definition =
                    realNode->getDefinitions();
            std::unique_ptr<Definition, default_delete<Definition>>::pointer operationDefinitioNotCasted =
                    definition[0].get();
            const GraphQLAstOperationDefinition *operationDefinitionCasted =
                    (const GraphQLAstOperationDefinition *) operationDefinitioNotCasted;
            const OperationDefinition *operationDefinition =
                    (const OperationDefinition *) operationDefinitionCasted;
            return operationDefinition;
        }



    }
}
