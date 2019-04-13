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
            std::map<char*, IGraphQlResolver*>* resolvers;
        public:
            ResolverManager();

            virtual ~ResolverManager();

        public:
            void registerResolver(IGraphQlResolver* resolver);

            IGraphQlDTO *executeResolver(char *resolverName, const std::vector<ResolverArgument> &args);

        };


    }
}

#endif //GRAPHQLCPP_RESOLVERMANAGER_H
