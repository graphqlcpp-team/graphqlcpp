//
// Created by julian on 11.04.19.
//

#ifndef GRAPHQLCPP_IGRAPHQLRESOLVER_H
#define GRAPHQLCPP_IGRAPHQLRESOLVER_H

#include "../IGraphQlDTO.h"
#include "ResolverArgument.h"
#include <vector>

namespace graphqlcpp {
    namespace resolver {
        using namespace graphqlcpp::api;
        class IGraphQlResolver {
        public:
            /**
             * This function must be overwritten.
             * Gets the resolver name.
             * @return The resolver name.
             */
            virtual std::string getResolverName() = 0;

            /**
             * D'stor.
             */
            virtual ~IGraphQlResolver();

            /**
             * This function must be overwritten by the user. This function is the callback function of the resolver.
             * It will be execute after the validation.
             * @param resolverArgs The arguments for the callback function.
             * @return The resulting IGraphQlDTO object.
             */
            virtual IGraphQlDTO *execute(const std::vector<ResolverArgument> resolverArgs) = 0;
        };
    }
}


#endif //GRAPHQLCPP_IGRAPHQLRESOLVER_H
