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
namespace api {

using namespace facebook::graphql::ast;

class QueryValidator {
public:
	QueryValidator();
	bool isQueryValid(Node* rootNodeSchema, Node* rootNodeQuery);
};

} /* namespace api */
} /* namespace graphqlcpp */

#endif /* QUERYVALIDATOR_H_ */
