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
            vector<IGraphQlDTO*> content;
        public:
            /**
             * C'stor.
             * If the top level is an array the GraphQLDTOMultiRoot class is necessary.
             * @param content
             */
            GraphQlDTOMultiRoot(vector<IGraphQlDTO*> content){
                this->content = content;
            }

            /**
             * This function will serialize the GraphQlDTO object.
             * For the root object "data" will be written to the JSON element which is the response.
             * @param serializer The MySerializer object.
             * @return The modified MySerializer object.
             */
            MySerializer *serialize(MySerializer *serializer) override {
                serializer->setVal("data", content);
                return serializer;
            }
        };
    }
}


#endif //GRAPHQLCPP_GRAPHQLDTOMULTIROOT_H
