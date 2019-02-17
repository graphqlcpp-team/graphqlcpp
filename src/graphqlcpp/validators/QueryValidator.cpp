/*
 * QueryValidator.cpp
 *
 *  Created on: 17.02.2019
 *      Author: amelie
 */

#include "QueryValidator.h"
#include "../../libgraphqlparser/c/GraphQLAst.h"
#include "../../libgraphqlparser/Ast.h"
#include <vector>

namespace graphqlcpp {
namespace validators {

QueryValidator::QueryValidator() {
	// TODO Auto-generated constructor stub

}


bool QueryValidator::isQueryValid(Node* rootNodeSchema,
		Node* rootNodeQuery) {
	getOperation(rootNodeQuery);
	return false;
}

using namespace std;
using namespace facebook::graphql;
using namespace facebook::graphql::ast;

const char* QueryValidator::getOperation(Node* rootNodeQuery) {

	auto graphQlAstDocument = (const struct GraphQLAstDocument *)rootNodeQuery;
 	const auto *realNode = (const Document *)graphQlAstDocument;
	const  std::vector<std::unique_ptr<Definition>>& x = realNode->getDefinitions();
	auto operationDefinitioNotCasted = x[0].get();
	auto operationDefinitionCasted = (const GraphQLAstOperationDefinition *)operationDefinitioNotCasted;
	const auto *realNodeOpDef = (const OperationDefinition *)operationDefinitionCasted;
	const char* operation = realNodeOpDef->getOperation();
	return operation;
	//auto def = realNode->getDefinitions();
	//auto arrayMt = def._M_impl._M_start->_M_t._M_t[1];

	//const char * operationDefinition = GraphQLAstOperationDefinition_get_operation((const GraphQLAstOperationDefinition*)rootNodeQuery);

}
} /* namespace api */
} /* namespace graphqlcpp */
