/*
 * QueryValidator.cpp
 *
 *  Created on: 17.02.2019
 *      Author: amelie
 */

#include "QueryValidator.h"
#include "../../libgraphqlparser/c/GraphQLAst.h"
#include "../../libgraphqlparser/Ast.h"
#include "../exceptions/WrongOperationException.h"
#include <vector>

namespace graphqlcpp {
namespace validators {

using namespace graphqlcpp::exceptions;

QueryValidator::QueryValidator(SchemaAstWraper* schemaWrapper) {
	this->schemaWrapper = schemaWrapper;

}
bool QueryValidator::isQueryValid(Node* rootNodeQuery) {
	const char* operation = getOperation(rootNodeQuery);
	if (operation != "query") {
		throw WrongOperationException();
		return false;
	}

	return false;
}

using namespace std;
using namespace facebook::graphql;
using namespace facebook::graphql::ast;

const char* QueryValidator::getOperation(Node* rootNodeQuery) {

	const GraphQLAstDocument* graphQlAstDocument =
			(const struct GraphQLAstDocument *) rootNodeQuery;
	const Document *realNode = (const Document *) graphQlAstDocument;
	const std::vector<std::unique_ptr<Definition>>& x =
			realNode->getDefinitions();
	std::unique_ptr<Definition, default_delete<Definition>>::pointer operationDefinitioNotCasted =
			x[0].get();
	const GraphQLAstOperationDefinition * operationDefinitionCasted =
			(const GraphQLAstOperationDefinition *) operationDefinitioNotCasted;
	const OperationDefinition *realNodeOpDef =
			(const OperationDefinition *) operationDefinitionCasted;
	const char* operation = realNodeOpDef->getOperation();
	return operation;
}

void QueryValidator::iterateThroughAST(Node* rootNodeQuery) {
	const GraphQLAstSelectionSet* selectionSet = getSelectionSet(rootNodeQuery);
	//do we need to operate through every operationDefinition?
	//Need to operate through every field

}

const GraphQLAstSelectionSet* QueryValidator::getSelectionSet(
		Node* rootNodeQuery) {
	const GraphQLAstDocument* graphQlAstDocument =
			(const struct GraphQLAstDocument *) rootNodeQuery;
	const Document *realNode = (const Document *) graphQlAstDocument;
	const std::vector<std::unique_ptr<Definition>>& x =
			realNode->getDefinitions();
	std::unique_ptr<Definition, default_delete<Definition>>::pointer operationDefinitioNotCasted =
			x[0].get();
	const GraphQLAstOperationDefinition * operationDefinitionCasted =
			(const GraphQLAstOperationDefinition *) operationDefinitioNotCasted;
	const OperationDefinition *realNodeOpDef =
			(const OperationDefinition *) operationDefinitionCasted;
	const GraphQLAstSelectionSet * selectionSet =
			(const struct GraphQLAstSelectionSet *) &realNodeOpDef->getSelectionSet();
	return selectionSet;
}

} /* namespace api */
} /* namespace graphqlcpp */
