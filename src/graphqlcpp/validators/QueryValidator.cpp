/*
 * QueryValidator.cpp
 *
 *  Created on: 17.02.2019
 *      Author: amelie
 */

#include "QueryValidator.h"

namespace graphqlcpp {
namespace validators {

QueryValidator::QueryValidator(SchemaAstWraper* schemaWrapper) {
	this->schemaWrapper = schemaWrapper;

}
bool QueryValidator::isQueryValid(Node* rootNodeQuery) {
}

} /* namespace api */
} /* namespace graphqlcpp */

