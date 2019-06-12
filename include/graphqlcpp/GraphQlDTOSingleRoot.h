//
// Created by julian on 12.06.19.
//

#ifndef GRAPHQLCPP_GRAPHQLDTOSINGLEROOT_H
#define GRAPHQLCPP_GRAPHQLDTOSINGLEROOT_H

#include "IGraphQlDTO.h"

namespace graphqlcpp {
    namespace api {
        class GraphQlDTOSingleRoot : public IGraphQlDTO {
        private:
            IGraphQlDTO* content;
        public:
            GraphQlDTOSingleRoot(IGraphQlDTO* content){
                this->content = content;
            }
            MySerializer *serialize(MySerializer *serializer) override {
                serializer->setVal("data", content);
                return serializer;
            }
        };
    }
}



#endif //GRAPHQLCPP_GRAPHQLDTOSINGLEROOT_H
