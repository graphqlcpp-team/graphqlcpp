//
// Created by amelie on 16.04.19.
//

#include "../../../include/graphqlcpp/resolver/ResolverInfo.h"

graphqlcpp::ResolverInfo::ResolverInfo(std::string resolverName, std::vector<ResolverArgument *> args) {
    this->resolverName = resolverName;
    this->args = args;
}

std::string graphqlcpp::ResolverInfo::getResolverName() {
    return this->resolverName;
}

std::vector<ResolverArgument *> graphqlcpp::ResolverInfo::getArgs() {
    return this->args;
}
