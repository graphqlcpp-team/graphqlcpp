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

        class InvalidQueryException : public runtime_error {
        public:
            InvalidQueryException() : runtime_error("invalid query") {};
        };

    } /* namespace api */
} /* namespace graphqlcpp */

#endif /* INVALIDSCHEMAEXCEPTION_H_ */
