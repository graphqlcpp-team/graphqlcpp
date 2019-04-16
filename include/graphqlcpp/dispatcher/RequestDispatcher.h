//
// Created by julian on 13.04.19.
//

#ifndef GRAPHQLCPP_REQUESTDISPATCHER_H
#define GRAPHQLCPP_REQUESTDISPATCHER_H

#include "../IGraphQlDTO.h"
#include "../resolver/ResolverManager.h"
#include "../validators/SchemaAstWraper.h"

namespace graphqlcpp {
    namespace dispatcher {
    using namespace api;
    using namespace resolver;
    using namespace validators;

        class RequestDispatcher {
        private:
            ResolverManager* resolverManager;
            SchemaAstWraper* schemaAstWraper;
            std::string getRequestType(Node* requestAst);
            //std::string getRes
        public:
            RequestDispatcher(ResolverManager* resolverManager, SchemaAstWraper* schemaAstWraper);
            IGraphQlDTO* executeRequest(Node* requestAst);
        };

    }
}

#endif //GRAPHQLCPP_REQUESTDISPATCHER_H
