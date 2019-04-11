//
// Created by julian on 05.04.19.
//

#ifndef IGRAPHQLDTO_H_
#define IGRAPHQLDTO_H_


#include "utils/MySerializer.h"

namespace graphqlcpp {
    namespace utils {
        class MySerializer;
    }
    namespace api {
        using namespace graphqlcpp::utils;

        class IGraphQlDTO {
        public:
            virtual MySerializer *serialize(MySerializer *serializer) = 0;

        };
    }
}

#endif //IGRAPHQLDTO_H_
