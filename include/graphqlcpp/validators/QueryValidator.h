/*
 * QueryValidator.h
 *
 *  Created on: 17.02.2019
 *      Author: amelie
 */

/** @file*/

#ifndef QUERYVALIDATOR_H_
#define QUERYVALIDATOR_H_

#include "SchemaAstWraper.h"
#include "../../graphqlparser/Ast.h"

namespace graphqlcpp {
    /**
     * namespace for validation
     */
namespace validators {

using namespace facebook::graphql::ast;

/**
 * validates the query
 */
class QueryValidator {
private:
    /**
     * An object of the schemaAstWrapper.
     */
	SchemaAstWraper* schemaWrapper;
    /**
    * This method will iterate through a selection set an validate every selection set which is a child.
    * A selection set is a node of the AST. The selection set is an array of all nodes which are located under
    * a node. It can be iterate over every element. This element contains the name and the arguments.
    * This method will validate if the name of this element exists as a child of the father element in the
    * schema AST. Therefore the name of the father node is a transfer parameter.
    * If the node exists as a child of the father, every argument will be validate.
    * If the arguments are valid, the method will call itself recursivly to validate the whole AST.
    * The method walks through the AST in preorder.
    * @param selectionSet The selection set which will be validate.
    * @param fatherFieldName The name of the father node element.
    * @return True, if the two validation steps were successful, otherwise false.
    */
	bool iterateThroughSelectionSetsAndValidate(const SelectionSet* selectionSet, const char* fatherFieldName);
    /**
     * This method gets the operation definition.
     * Out of the operation definition the operation can be extracted. Also the selection set of the root node
     * is located in the operation definition.
     * In both ways the operation definition must be determined.
     * @param rootNodeQuery The root node of the query AST.
     * @return The operation definition.
     */
	const OperationDefinition* getOperationDefinition(Node *rootNodeQuery);
public:
    /**
     * This method gets the selection set of the root node.
     * Only the root note is of type node. Afterwards the nodes are of type selection set.
     * @param rootNodeQuery The root node of the query AST.
     * @return The selection set of the root node.
     */
	const SelectionSet* getSelectionSet(Node* rootNodeQuery);
    /**
     * This method gets the operation of the query.
     * @param rootNodeQuery The root node of the query AST.
     * @return The operation.
     */
	const char* getOperation(Node* rootNodeQuery);
    /**
     * Constructor of the query validator class.
     * Needs an object of the schemaAstWrapper because the validation query vs schema will be done by the
     * schemaAstWrapper. The schemaAstWrapper contains the schema AST for this specific query.
     * @param schemaWrapper An object of the schemaAstWrapper.
     */
	explicit QueryValidator(SchemaAstWraper* schemaWrapper);
    /**
     * This method checks if a query is valid.
     * Checks if the operation of the query is a valid operation given in the schema.
     * Every node of the query (element of the query) will be validate against the schema.
     * It will check if a node of the query exists under the same father element as in the schema.
     * Every argument of the query will be validate against the schema.
     * @param rootNodeQuery The root node of the query AST.
     * @return True, if the query is valid, otherwise false.
     * @throw InvalidQueryExceprion if the query is not valid.
     * @throw WrongOperationException if the operation is not set in the schema.
     */
	bool isQueryValid(Node* rootNodeQuery);
};

} /* namespace api */
} /* namespace graphqlcpp */

#endif /* QUERYVALIDATOR_H_ */
