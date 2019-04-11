//
// Created by julian on 11.04.19.
//

#ifndef GRAPHQLCPP_IGRAPHQLRESOLVER_H
#define GRAPHQLCPP_IGRAPHQLRESOLVER_H

#include "../IGraphQlDTO.h"
#include "ResolverArgument.h"

namespace graphqlcpp {
    namespace resolver {
        using namespace graphqlcpp::api;
        class IGraphQlResolver {
        public:
            virtual char *getResolverName() = 0;
            virtual IGraphQlDTO execute(ResolverArgument resolverArgs[])=0;
        };
    }
}


#endif //GRAPHQLCPP_IGRAPHQLRESOLVER_H
