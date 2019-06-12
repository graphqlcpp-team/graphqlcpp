//
// Created by julian on 12.06.19.
//

#ifndef GRAPHQLCPP_GRAPHQLDTOMULTIROOT_H
#define GRAPHQLCPP_GRAPHQLDTOMULTIROOT_H

#include "IGraphQlDTO.h"
#include <vector>

namespace graphqlcpp {
    namespace api {

        using namespace std;
        class GraphQlDTOMultiRoot : public IGraphQlDTO {
        private:
            vector<IGraphQlDTO> content;
        public:
            GraphQlDTOMultiRoot(vector<IGraphQlDTO> content){
                this->content = content;
            }
            MySerializer *serialize(MySerializer *serializer) override {
                serializer->setVal("data", content);
                return serializer;
            }
        };
    }
}


#endif //GRAPHQLCPP_GRAPHQLDTOMULTIROOT_H
