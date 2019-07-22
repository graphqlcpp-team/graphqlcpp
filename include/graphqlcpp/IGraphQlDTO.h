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
            /**
             * This function must be overwritten by the user. It will serialize the GraphQLDTO object.
             * @param serializer The MySerializer object.
             * @return The modified MySerializer object.
             */
            virtual MySerializer *serialize(MySerializer *serializer) = 0;

        };
    }
}

#endif //IGRAPHQLDTO_H_
