//
// Created by amelie on 07.04.19.
//

#ifndef GRAPHQLCPP_ARGUMENTNOTVALIDEXCEPTION_H
#define GRAPHQLCPP_ARGUMENTNOTVALIDEXCEPTION_H

#include <stdexcept>

namespace graphqlcpp {
    namespace exceptions {
        using namespace std;

        class ArgumentNotValidException : public runtime_error {
        public:
            ArgumentNotValidException() : runtime_error("the argument is not valid") {};
        };

    } /* namespace api */
} /* namespace graphqlcpp */

#endif //GRAPHQLCPP_ARGUMENTNOTVALIDEXCEPTION_H
