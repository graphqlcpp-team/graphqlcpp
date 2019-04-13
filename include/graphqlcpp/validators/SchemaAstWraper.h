/*
 * SchemaAstWraper.h
 *
 *  Created on: 17.02.2019
 *      Author: julian2
 */

#ifndef SCHEMAASTWRAPER_H_
#define SCHEMAASTWRAPER_H_

#include <memory>
#include <vector>
#include "../../graphqlparser/Ast.h"

namespace graphqlcpp {
namespace validators {

using namespace facebook::graphql::ast;

class SchemaAstWraper {
private:
	Node* schema = nullptr;


public:
    explicit SchemaAstWraper(Node* schemaAstRootNode);
	const char* printSchemaAsJson();
	bool isOperationValid(const char* operation);
	bool validateNode(const char* fatherFieldName, const Field * field);
private:
    const Document* getDocument();
    const SchemaDefinition* getSchemaDefinition();
	bool validateArgument(const char *valueType, const Value* value);

    const char *getFatherFieldNameIfFatherIsOperation(const char *fatherFieldName);

    const char *getFatherNodeNameIfFatherIsNotOperation(const char *fatherFieldName,
            const std::vector<std::unique_ptr<Definition>> & operationDefinitions);

	bool fieldExistsAsChildOfFatherNodeWithRigthArguments(const Field *fieldQueryAst,
														  const std::vector<std::unique_ptr<Definition>> &operationDefinition,
														  const char *fatherNodeName);

	bool checkArguments(const std::vector<std::unique_ptr<Argument>> *argumentsQueryAst,
						const std::vector<std::unique_ptr<InputValueDefinition>> *argumentsSchemaAst);

	const Value * checkIfQueryContainsArgument(const std::vector<std::unique_ptr<Argument>> *argumentsQueryAst,
											 const char *argumentSchemaAstName, bool nullable);
};

} /* namespace validators */
} /* namespace graphqlcpp */

#endif /* SCHEMAASTWRAPER_H_ */
