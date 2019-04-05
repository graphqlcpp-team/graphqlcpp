//
// Created by julian on 05.04.19.
//

#ifndef GRAPHQLCPP_SERIALIZER_H
#define GRAPHQLCPP_SERIALIZER_H


#include <jsoncpp/json/value.h>
#include "IGraphQlDTO.h"
#include "../../include/graphqlparser/AstNode.h"

class Serializer {

    using namespace facebook::graphql;

private:
    Json::Value jsonStruct;

public:
    Serializer(Node* currentRootNode);


    void setVal(char** name, int val);
    void setVal(char** name, char** val);
    void setVal(char** name, bool val);
    void setVal(char** name, IGraphQlDTO* val);

private:
    bool wasFieldRequested(char** fieldName);
};


#endif //GRAPHQLCPP_SERIALIZER_H
