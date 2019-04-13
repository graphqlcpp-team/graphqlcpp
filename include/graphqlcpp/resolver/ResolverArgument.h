//
// Created by julian on 11.04.19.
//

#ifndef GRAPHQLCPP_RESOLVERARGUMENT_H
#define GRAPHQLCPP_RESOLVERARGUMENT_H


class ResolverArgument {
private:
    char* argName;
    //TODO: typiesieren
    void* argValue;
public:
    ResolverArgument(char *argName, void *argValue);

    char *getArgName() const;

    void *getArgValue() const;

};


#endif //GRAPHQLCPP_RESOLVERARGUMENT_H
