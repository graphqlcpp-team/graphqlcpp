/*
 * SchemaValidator.h
 *
 *  Created on: 10.02.2019
 *      Author: admin
 */

#ifndef SCHEMAVALIDATOR_H_
#define SCHEMAVALIDATOR_H_

#include "libgraphqlparser/Ast.h"

namespace graphqlcpp {
namespace validators{
using namespace facebook::graphql::ast;

class SchemaValidator {
private:
	int test = 1;
public:
	SchemaValidator();
	bool checkIfSchemaIsValid(Node* schemaAst);
};

} /* namespace graphqlcppvalidators */
}
#endif /* SCHEMAVALIDATOR_H_ */
