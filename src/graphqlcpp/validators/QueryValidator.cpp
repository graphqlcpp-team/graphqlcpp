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

        QueryValidator::QueryValidator(SchemaAstWraper *schemaWrapper) {
            this->schemaWrapper = schemaWrapper;

        }

        bool QueryValidator::isQueryValid(Node *rootNodeQuery) {
            const char *operation = getOperation(rootNodeQuery);
            const SelectionSet *selectionSet = getSelectionSet(rootNodeQuery);
            char nullChar = '\0';
            //const char *firstElement = &nullChar;
            if (!iterateThroughSelectionSetsAndValidate(selectionSet, operation)) {
                throw InvalidQueryException();
                return false;
            }
            const char *query = "query";
            const char *mutation = "mutation";
            if (strcmp(operation, query) !=
                0 /*|| strcmp(operation, mutation) TODO if we support mutation uncomment it*/) {
                throw WrongOperationException();
                return false;
            }

            return false;
        }

        using namespace std;
        using namespace facebook::graphql;
        using namespace facebook::graphql::ast;

/**
 * Preorder
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

                    //call method which will validate if the node exists as child of the father node.
                    if (!this->schemaWrapper->nodeExsitstsAsChildOf(name,
                                                                    fatherFieldName)) {
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
                //call method to validate the argument

                cout << "Name Argument: " << nameAr << endl;

                index++;
            }
            return true;
        }

        const char *QueryValidator::getOperation(Node *rootNodeQuery) {
            const OperationDefinition *realNodeOpDef = getOperationDefinition(
                    rootNodeQuery);
            const char *operation = realNodeOpDef->getOperation();
            return operation;
        }

        const SelectionSet *QueryValidator::getSelectionSet(Node *rootNodeQuery) {
            const OperationDefinition *realNodeOpDef = getOperationDefinition(
                    rootNodeQuery);
            const GraphQLAstSelectionSet *graphQlSelectionSet =
                    (const struct GraphQLAstSelectionSet *) &realNodeOpDef->getSelectionSet();
            const SelectionSet *selectionSet =
                    (const SelectionSet *) graphQlSelectionSet;
            return selectionSet;
        }

        const OperationDefinition *QueryValidator::getOperationDefinition(
                Node *rootNodeQuery) {
            const GraphQLAstDocument *graphQlAstDocument =
                    (const struct GraphQLAstDocument *) rootNodeQuery;
            const Document *realNode = (const Document *) graphQlAstDocument;
            const std::vector<std::unique_ptr<Definition>> &x =
                    realNode->getDefinitions();
            std::unique_ptr<Definition, default_delete<Definition>>::pointer operationDefinitioNotCasted =
                    x[0].get();
            const GraphQLAstOperationDefinition *operationDefinitionCasted =
                    (const GraphQLAstOperationDefinition *) operationDefinitioNotCasted;
            const OperationDefinition *realNodeOpDef =
                    (const OperationDefinition *) operationDefinitionCasted;
            return realNodeOpDef;
        }

/*void QueryValidator::iterateThroughAST(Node* rootNodeQuery) {
 const GraphQLAstSelectionSet* selectionSet = getSelectionSet(rootNodeQuery);
 //do we need to operate through every operationDefinition?
 //Need to operate through every field

 const std::vector<std::unique_ptr<Selection>>& selec =
 realNode->getSelections();

 const GraphQLAstField* graphQlAstFiel = (GraphQLAstField*) selec[0].get();
 const Field* realNodeField = (const Field *) graphQlAstFiel;
 const Name* name = &realNodeField->getName();

 const char* nameOfField = name->getValue();

 const SelectionSet* selectionSetn = realNodeField->getSelectionSet();
 const std::vector<std::unique_ptr<Selection>>& selecN =
 selectionSetn->getSelections();
 int index = 0;
 for (auto i = selecN.begin(); i != selecN.end(); ++i) {
 const GraphQLAstField* graphQlAstFielN =
 (GraphQLAstField*) selecN[index].get();
 const Field* realNodeFieldN = (const Field *) graphQlAstFielN;
 const auto nameNN = &realNodeFieldN->getName();
 auto nameNNN = nameNN->getValue();
 index++;
 }

 auto sizeA = sizeof(&selecN);
 auto sizeB = sizeof(selecN);
 //auto sizeC = sizeof(*selecN);
 size_t size = sizeof(&selecN) / sizeof(selecN);
 //const __gnu_cxx::__alloc_traits<allocator<unique_ptr<Selection,default_delete<Selection>>>>::value_type test = selecN[0];
 for (unsigned int a = 0; a < size; a = a + 1) {
 }

 //const auto name =   (const struct GraphQLAstName *)&realNodeField->getName();
 //const Selection* field = (Selection*)selec[0];
 //const auto selection = realNode->getSelections();

 }*/

    } /* namespace api */
} /* namespace graphqlcpp */
