/*
 * WrongOperationException.h
 *
 *  Created on: 17.02.2019
 *      Author: amelie
 */

#ifndef WRONGOPERATIONEXCEPTION_H_
#define WRONGOPERATIONEXCEPTION_H_
#include <stdexcept>
namespace graphqlcpp {
namespace exceptions {
using namespace std;
class WrongOperationException : public runtime_error {
public:
	WrongOperationException() : runtime_error("only query operations are allowed"){};
};

} /* namespace api */
} /* namespace graphqlcpp */

#endif /* INVALIDSCHEMAEXCEPTION_H_ */
