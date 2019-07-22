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
            /**
             * C'stor.
             * If the top level is an array the GraphQLDTOMultiRoot class is necessary.
             * @param content
             */
            GraphQlDTOSingleRoot(IGraphQlDTO* content){
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



#endif //GRAPHQLCPP_GRAPHQLDTOSINGLEROOT_H
