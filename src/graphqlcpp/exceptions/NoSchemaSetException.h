/*
 * NoSchemaSetException.h
 *
 *  Created on: 17.02.2019
 *      Author: amelie
 */

#ifndef NOSCHEMASETEXCEPTION_H_
#define NOSCHEMASETEXCEPTION_H_

#include <stdexcept>

namespace graphqlcpp {
namespace exceptions {
using namespace std;

class NoSchemaSetException : public runtime_error {
public:
	NoSchemaSetException() : runtime_error("no schema set"){};
};

} /* namespace api */
} /* namespace graphqlcpp */

#endif /* NOSCHEMASETEXCEPTION_H_ */
