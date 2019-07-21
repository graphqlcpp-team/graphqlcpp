/*
 * NoSchemaSetException.h
 *
 *  Created on: 17.02.2019
 *      Author: amelie
 */

#ifndef ArgumentNotValidException_H_
#define ArgumentNotValidException_H_

#include <stdexcept>

namespace graphqlcpp {
namespace exceptions {
using namespace std;

/**
 * Will be thrown if the argument is not valid
 */
class ArgumentNotValidException : public runtime_error {
public:
	ArgumentNotValidException() : runtime_error("argument is not valid"){};
};

} /* namespace api */
} /* namespace graphqlcpp */

#endif /* ArgumentNotValidException_H_ */
