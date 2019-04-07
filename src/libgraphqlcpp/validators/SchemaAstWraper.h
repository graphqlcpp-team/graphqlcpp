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
	bool nodeExistsAsChildOf(const char* childFieldName, const char* fatherFieldName);
	bool isOperationValid(const char* operation);
	bool isArgumentValid(const char* name, const Value* value, const char* fieldName);

private:
    const Document* getDocument();
    const char* getOperationName(int index);
    const SchemaDefinition* getSchemaDefinition();
    //const std::vector<std::unique_ptr<Definition>> getOperationDefinition();
	bool iterateThroughArgumentsAndValidate(const std::vector <std::unique_ptr<InputValueDefinition>>* arguments,
	        const char* argumentName, const Value* value);
	bool validateArgument(const std::unique_ptr <InputValueDefinition> * argument, const Value* value);

    const char *getFatherFieldNameIfFatherIsOperatiom(const char *fatherFieldName);

    const char *getFatherNodeNameIfFatherIsNotOperation(const char *fatherFieldName,
            const std::vector<std::unique_ptr<Definition>> & definition);

    bool fieldExistsAsChildOfFatherNode(const char *childFieldName,
            const std::vector<std::unique_ptr < Definition>> & operationDefintion, const char* fatherNodeName);

};

} /* namespace validators */
} /* namespace graphqlcpp */

#endif /* SCHEMAASTWRAPER_H_ */
