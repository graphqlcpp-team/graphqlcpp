//
// Created by julian on 05.04.19.
//

#ifndef GRAPHQLCPP_IGRAPHQLDTO_H
#define GRAPHQLCPP_IGRAPHQLDTO_H


#include "Serializer.h"

class IGraphQlDTO {
public:
    virtual Serializer asJson(Serializer ser) = 0;
protected:
    IGraphQlDTO(Serializer ser);
};


#endif //GRAPHQLCPP_IGRAPHQLDTO_H
