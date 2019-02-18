/*
 * QueryValidator.h
 *
 *  Created on: 17.02.2019
 *      Author: amelie
 */

#ifndef QUERYVALIDATOR_H_
#define QUERYVALIDATOR_H_

#include "SchemaAstWraper.h"
#include "../../libgraphqlparser/Ast.h"


namespace graphqlcpp {
namespace validators {

using namespace facebook::graphql::ast;

class QueryValidator {
private:
	SchemaAstWraper* schemaWrapper;
public:
	QueryValidator(SchemaAstWraper* schemaWrapper);
	bool isQueryValid(Node* rootNodeQuery);
};

} /* namespace api */
} /* namespace graphqlcpp */

#endif /* QUERYVALIDATOR_H_ */
