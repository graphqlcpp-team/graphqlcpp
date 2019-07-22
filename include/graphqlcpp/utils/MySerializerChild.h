//
// Created by julian on 12.06.19.
//

#ifndef GRAPHQLCPP_MYSERIALIZERCHILD_H
#define GRAPHQLCPP_MYSERIALIZERCHILD_H

#include "MySerializer.h"

namespace graphqlcpp {
    namespace utils {

        class MySerializerChild : public MySerializer{
        public:
            /**
             * C'stor.
             * @param selectionSetOfCurrentLevel The selection set of the current level in the query AST.
             */
            MySerializerChild(const SelectionSet *selectionSetOfCurrentLevel);
        protected:
             /**
             * This function will validate if the resolver field is requested.
             * It will validate if the fieldName is a part of the query at the current level in the query AST.
             * @param fieldName The name of the serializer.
             * @return True, if the fieldName is part of the query AST, otherwise false.
             */
            bool wasFieldRequested(std::string fieldName) override;
        };
    }
}


#endif //GRAPHQLCPP_MYSERIALIZERCHILD_H
