/*
 * SchemaAstWraper.cpp
 *
 *  Created on: 17.02.2019
 *      Author: julian2
 */

#include "SchemaAstWraper.h"
#include "../../libgraphqlparser/c/GraphQLAstToJSON.h"
#include "../../libgraphqlparser/Ast.h"
#include "../exceptions/NoSchemaSetException.h"

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


} /* namespace validators */
} /* namespace graphqlcpp */

