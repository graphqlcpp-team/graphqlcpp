//
// Created by julian on 11.04.19.
//

#ifndef GRAPHQLCPP_RESOLVERARGUMENT_H
#define GRAPHQLCPP_RESOLVERARGUMENT_H

#include <string>

class ResolverArgument {
private:
    /**
     * Argument name.
     */
    std::string argName;
    /**
     * Arguemnt value.
     */
    std::string argValue;
public:
    /**
     * The arguments of the query AST are stored here.
     * They are used to call the resolver with arguments out of the query AST.
     * @param argName The name of the argument.
     * @param argValue The value of the argument.
     */
    ResolverArgument(std::string argName, std::string argValue);

    /**
     * Getter of the argument name.
     * @return The argument name.
     */
    std::string getArgName() const;

    /**
     * Getter of the argument value.
     * @return The argument value.
     */
    std::string getArgValue() const;

};


#endif //GRAPHQLCPP_RESOLVERARGUMENT_H
