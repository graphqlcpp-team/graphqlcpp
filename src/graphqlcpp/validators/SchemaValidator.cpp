/*
 * SchemaValidator.cpp
 *
 *  Created on: 10.02.2019
 *      Author: admin
 */

#include "../../../include/graphqlcpp/validators/SchemaValidator.h"

namespace graphqlcpp{
namespace validators{

SchemaValidator::SchemaValidator() {
    //there is no need for schema validation at the moment
}

bool SchemaValidator::checkIfSchemaIsValid(
		Node* schemaAst) {
	return true;
	//if you want to implement schema validation then you can implement it here
}
}
}
