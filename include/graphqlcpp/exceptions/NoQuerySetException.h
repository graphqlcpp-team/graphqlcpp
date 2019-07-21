/*
 * NoSchemaSetException.h
 *
 *  Created on: 17.02.2019
 *      Author: amelie
 */

#ifndef NOQUERYSETEXCEPTION_H_
#define NOQUERYSETEXCEPTION_H_

#include <stdexcept>

namespace graphqlcpp {
namespace exceptions {
using namespace std;

class NoQuerySetException : public runtime_error {
public:
    NoQuerySetException() : runtime_error("no query set"){};
};

} /* namespace api */
} /* namespace graphqlcpp */

#endif /* NOSCHEMASETEXCEPTION_H_ */
