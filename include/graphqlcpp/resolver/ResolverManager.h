//
// Created by julian on 11.04.19.
//

#ifndef GRAPHQLCPP_RESOLVERMANAGER_H
#define GRAPHQLCPP_RESOLVERMANAGER_H

#include "IGraphQlResolver.h"
#include "../IGraphQlDTO.h"
#include "ResolverArgument.h"
#include <map>
#include <vector>

namespace graphqlcpp {
    namespace resolver {
        using namespace api;
        class ResolverManager {
        private:
            /**
             * Key: name of the resolver.
             * Value: resolver.
             */
            std::map<std::string, IGraphQlResolver*>* resolvers;
        public:
            /**
             * C'stor.
             * Will create a map and store it in resolvers.
             */
            ResolverManager();

            /**
             * D'stor.
             * Delete all entries of the map resolvers.
             */
            virtual ~ResolverManager();

        public:
            /**
             * This function will add a IGraphQlResolver to the map resolvers.
             * @param resolver The resolver to add.
             */
            void registerResolver(IGraphQlResolver* resolver);

            /**
             * This function will start the execution of a resolver method.
             * The resolverName will be searched in the map "resolvers". The resolver method will be executed
             * with arguments arg.
             * @param resolverName The name of the resolver, which should be executed.
             * @param args The arguments which should be passed to the resolver method.
             * @return The IGraphQLSto object.
             */
            IGraphQlDTO *executeResolver(std::string resolverName, const std::vector<ResolverArgument> args);

        };


    }
}

#endif //GRAPHQLCPP_RESOLVERMANAGER_H
