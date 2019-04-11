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

class ArgumentNotValidException : public runtime_error {
public:
	ArgumentNotValidException() : runtime_error("no schema set"){};
};

} /* namespace api */
} /* namespace graphqlcpp */

#endif /* ArgumentNotValidException_H_ */
