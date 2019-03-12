/*
 * SchemaAstWraper.h
 *
 *  Created on: 17.02.2019
 *      Author: julian2
 */

#ifndef SCHEMAASTWRAPER_H_
#define SCHEMAASTWRAPER_H_

#include "../../libgraphqlparser/Ast.h"

namespace graphqlcpp {
namespace validators {

using namespace facebook::graphql::ast;

class SchemaAstWraper {
private:
	Node* schema = nullptr;


public:
	SchemaAstWraper(Node* schemaAstRootNode);
	const char* printSchemaAsJson();
	bool nodeExsitstsAsChildOf(const char* childFieldName, const char* fatherFieldName);
	bool isOperationValid(const char* operation);

private:
    const Document* getDocument();
    const char* getOperationName(int index);
    const SchemaDefinition* getSchemaDefinition();
    //const std::vector<std::unique_ptr<Definition>> getOperationDefinition();
	void iterateThoughAst();

};

} /* namespace validators */
} /* namespace graphqlcpp */

#endif /* SCHEMAASTWRAPER_H_ */
