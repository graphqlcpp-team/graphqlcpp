//
// Created by amelie on 16.04.19.
//

#ifndef GRAPHQLCPP_RESOLVERINFO_H
#define GRAPHQLCPP_RESOLVERINFO_H

#include <string>
#include <vector>
#include "../../../include/graphqlcpp/resolver/ResolverArgument.h"

namespace graphqlcpp {

    class ResolverInfo {
    private:
        /**
         * The name of the resolver which has to be executed because of the query.
         */
        std::string resolverName;
        /**
         * The arguments for the resolver which has to be executed because of the query.
         */
        std::vector<ResolverArgument> args;
    public:
        /**
         * C'stor.
         * @param resolverName The name of the resolver which has to be executed because of the query.
         * @param args The arguments for the resolver which has to be executed because of the query.
         */
        ResolverInfo(std::string resolverName, std::vector<ResolverArgument> args);

        /**
         * Getter of resolver name.
         * @return TTe name of the resolver which has to be executed because of the query.
         */
         std::string getResolverName();

         /**
          * Getter of the arguments.
          * @return The arguments for the resolver which has to be executed because of the query.
          */
         std::vector<ResolverArgument> getArgs();
    };

}
#endif //GRAPHQLCPP_RESOLVERINFO_H
