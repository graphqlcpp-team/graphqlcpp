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
            MySerializerChild(const SelectionSet *selectionSetOfCurrentLevel);
        protected:

            bool wasFieldRequested(std::string fieldName) override;
        };
    }
}


#endif //GRAPHQLCPP_MYSERIALIZERCHILD_H
