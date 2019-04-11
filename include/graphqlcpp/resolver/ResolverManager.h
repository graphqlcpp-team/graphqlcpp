//
// Created by julian on 11.04.19.
//

#ifndef GRAPHQLCPP_RESOLVERMANAGER_H
#define GRAPHQLCPP_RESOLVERMANAGER_H

#include "IGraphQlResolver.h"
#include "../IGraphQlDTO.h"
#include <map>

namespace graphqlcpp {
    namespace resolver {
        class ResolverManager {
        private:
            std::map<char*, IGraphQlResolver*>* resolvers;
        public:
            ResolverManager();

            virtual ~ResolverManager();

        public:
            void registerResolver(IGraphQlResolver* resolver);
            IGraphQlDTO executeResolver(char* resolverName );

        };


    }
}

#endif //GRAPHQLCPP_RESOLVERMANAGER_H
