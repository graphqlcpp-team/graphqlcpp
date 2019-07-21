//
// Created by julian on 12.06.19.
//

#ifndef GRAPHQLCPP_MYSERIALIZERROOT_H
#define GRAPHQLCPP_MYSERIALIZERROOT_H

#include "MySerializer.h"

namespace graphqlcpp{
    namespace utils{
        class MySerializerRoot : public MySerializer {
        protected:
            bool wasFieldRequested(std::string fieldName) override;
        public:
            MySerializerRoot(const SelectionSet *selectionSetOfCurrentLevel);

        };
    }
}



#endif //GRAPHQLCPP_MYSERIALIZERROOT_H
