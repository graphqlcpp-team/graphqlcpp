/*
 * SchemaAstWraper.cpp
 *
 *  Created on: 17.02.2019
 *      Author: julian2
 */

#include "exceptions/NoSchemaSetException.h"
#include "SchemaAstWraper.h"
#include "../../libgraphqlparser/c/GraphQLAstToJSON.h"

namespace graphqlcpp {
namespace validators {

using namespace facebook::graphql;
using namespace graphqlcpp::exceptions;

SchemaAstWraper::SchemaAstWraper(
		Node* schemaAstRootNode) {
	this->schema = schemaAstRootNode;
}
const char* SchemaAstWraper::printSchemaAsJson() {
	if(schema!=nullptr){
	const char *json = graphql_ast_to_json(
			(const struct GraphQLAstNode *) schema);
	return json;
	}
	throw NoSchemaSetException();
}

    bool SchemaAstWraper::nodeExsitstsAsChildOf(const char *fieldName, const char *oldFieldName) {
        cout << fieldName << endl;
        cout << oldFieldName << endl;
        return true;

    }


/*
bool SchemaAstWraper::nodeExsitstsAsChildOf() {
	//uebergabe parameter zwei knoten father, child
	//durch schema gehen und prüfen ob knoten child ein kind von father ist
//	const GraphQLAstDocument* graphQlAstDocument =
//				(const struct GraphQLAstDocument *) this->schema;
//	const Document *realNode = (const Document *) graphQlAstDocument;
//	const std::vector<std::unique_ptr<Definition>>& x =
//			realNode->getDefinitions();
//	std::unique_ptr<Definition, default_delete<Definition>>::pointer operationDefinitioNotCasted =
//			x[0].get();
//	const GraphQLAstOperationDefinition * operationDefinitionCasted =
//			(const GraphQLAstOperationDefinition *) operationDefinitioNotCasted;
//	const OperationDefinition *realNodeOpDef =
//			(const OperationDefinition *) operationDefinitionCasted;
//	const char* operation = realNodeOpDef->getOperation();
	//	return operation;

	return true;
}
 */

} /* namespace validators */
} /* namespace graphqlcpp */


