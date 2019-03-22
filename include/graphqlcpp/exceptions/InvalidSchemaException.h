/*
 * InvalidSchemaException.h
 *
 *  Created on: 17.02.2019
 *      Author: amelie
 */

#ifndef INVALIDSCHEMAEXCEPTION_H_
#define INVALIDSCHEMAEXCEPTION_H_
#include <stdexcept>
namespace graphqlcpp {
namespace exceptions {
using namespace std;
class InvalidSchemaException : public runtime_error {
public:
	InvalidSchemaException() : runtime_error("invalid schema"){};
};

} /* namespace api */
} /* namespace graphqlcpp */

#endif /* INVALIDSCHEMAEXCEPTION_H_ */
