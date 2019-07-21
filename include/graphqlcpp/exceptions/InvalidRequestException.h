/*
 * InvalidRequestException.h
 *
 *  Created on: 17.02.2019
 *      Author: amelie
 */

#ifndef INVALIDREQUESTEXCEPTION_H_
#define INVALIDREQUESTEXCEPTION_H_

#include <stdexcept>

namespace graphqlcpp {
    namespace exceptions {
        using namespace std;

        /**
         * Will be thrown if the request was invalid.
         */
        class InvalidRequestException : public runtime_error {
        public:
            InvalidRequestException() : runtime_error("invalid query") {};
        };

    } /* namespace api */
} /* namespace graphqlcpp */

#endif /* INVALIDREQUESTEXCEPTION_H_ */
