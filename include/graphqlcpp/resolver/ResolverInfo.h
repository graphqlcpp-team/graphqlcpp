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
        std::string resolverName;
        std::vector<ResolverArgument*> *args;
    public:
        ResolverInfo(std::string resolverName, std::vector<ResolverArgument*> *args);

         std::string getResolverName();

         std::vector<ResolverArgument*> *getArgs();
    };

}
#endif //GRAPHQLCPP_RESOLVERINFO_H
