//
// Created by julian on 11.04.19.
//

#ifndef GRAPHQLCPP_RESOLVERARGUMENT_H
#define GRAPHQLCPP_RESOLVERARGUMENT_H

#include <string>

class ResolverArgument {
private:
    std::string argName;
    std::string argValue;
public:
    ResolverArgument(std::string argName, std::string argValue);

    std::string getArgName() const;

    std::string getArgValue() const;

};


#endif //GRAPHQLCPP_RESOLVERARGUMENT_H
