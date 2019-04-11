//
// Created by julian on 11.04.19.
//

#include "../../../include/graphqlcpp/resolver/ResolverArgument.h"

char *ResolverArgument::getArgName() const {
    return argName;
}

void *ResolverArgument::getArgValue() const {
    return argValue;
}

ResolverArgument::ResolverArgument(char *argName, void *argValue) : argName(argName), argValue(argValue) {}
