/*
 * QueryValidator.h
 *
 *  Created on: 17.02.2019
 *      Author: amelie
 */

#ifndef QUERYVALIDATOR_H_
#define QUERYVALIDATOR_H_

#include "SchemaAstWraper.h"
#include "../../libgraphqlparser/Ast.h"
#include "../../libgraphqlparser/c/GraphQLAst.h"

namespace graphqlcpp {
namespace validators {

using namespace facebook::graphql::ast;

class QueryValidator {
private:
	SchemaAstWraper* schemaWrapper;
	void iterateThroughAST(Node* rootNodeQuery);
	bool iterateThroughSelectionSetsAndValidate(const SelectionSet* selectionSet, const char* oldFieldName);
	const SelectionSet* getSelectionSet(Node* rootNodeQuery);
	const OperationDefinition* getOperationDefinition(Node *rootNodeQuery);
	bool iterateThroughArgumentsOfOneFiledAndValidate(const Field* field);
public:
	const char* getOperation(Node* rootNodeQuery);
	QueryValidator(SchemaAstWraper* schemaWrapper);
	bool isQueryValid(Node* rootNodeQuery);
};

} /* namespace api */
} /* namespace graphqlcpp */

#endif /* QUERYVALIDATOR_H_ */
