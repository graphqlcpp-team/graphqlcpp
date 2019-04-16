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
    public:
        ResolverInfo(const std::string &resolverName, const std::vector<ResolverArgument> &args);

        const std::string &getResolverName() const;

        const std::vector<ResolverArgument> &getArgs() const;

    private:
        std::vector<ResolverArgument> args;
    };

}
#endif //GRAPHQLCPP_RESOLVERINFO_H
