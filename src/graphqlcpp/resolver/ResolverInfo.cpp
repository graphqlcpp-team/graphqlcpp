//
// Created by amelie on 16.04.19.
//

#include "../../../include/graphqlcpp/resolver/ResolverInfo.h"

const std::string &graphqlcpp::ResolverInfo::getResolverName() const {
    return resolverName;
}

const std::vector<ResolverArgument> &graphqlcpp::ResolverInfo::getArgs() const {
    return args;
}

graphqlcpp::ResolverInfo::ResolverInfo(const std::string &resolverName, const std::vector<ResolverArgument> &args)
        : resolverName(resolverName), args(args) {}
