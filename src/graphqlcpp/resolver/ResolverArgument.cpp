//
// Created by julian on 11.04.19.
//

#include "../../../include/graphqlcpp/resolver/ResolverArgument.h"

ResolverArgument::ResolverArgument(std::string argName, std::string argValue) {
    this->argName = argName;
    this->argValue = argValue;
}

std::string ResolverArgument::getArgName() const {
    return this->argName;
}

std::string ResolverArgument::getArgValue() const {
    return this->argValue;
}
