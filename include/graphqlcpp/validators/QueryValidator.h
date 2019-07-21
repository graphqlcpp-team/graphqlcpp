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
	SchemaAstWraper* schemaWrapper;
	bool iterateThroughSelectionSetsAndValidate(const SelectionSet* selectionSet, const char* fatherFieldName);
	const OperationDefinition* getOperationDefinition(Node *rootNodeQuery);
public:
	const SelectionSet* getSelectionSet(Node* rootNodeQuery);
	const char* getOperation(Node* rootNodeQuery);
	explicit QueryValidator(SchemaAstWraper* schemaWrapper);
	bool isQueryValid(Node* rootNodeQuery);
};

} /* namespace api */
} /* namespace graphqlcpp */

#endif /* QUERYVALIDATOR_H_ */
