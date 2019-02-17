/*
 * QueryValidator.h
 *
 *  Created on: 17.02.2019
 *      Author: amelie
 */

#ifndef QUERYVALIDATOR_H_
#define QUERYVALIDATOR_H_

#include "../../libgraphqlparser/Ast.h"

namespace graphqlcpp {
namespace validators {

using namespace facebook::graphql::ast;

class QueryValidator {
public:
	QueryValidator();
	bool isQueryValid(Node* rootNodeSchema, Node* rootNodeQuery);
	const char* getOperation(Node* rootNodeQuery);
};

} /* namespace api */
} /* namespace graphqlcpp */

#endif /* QUERYVALIDATOR_H_ */
