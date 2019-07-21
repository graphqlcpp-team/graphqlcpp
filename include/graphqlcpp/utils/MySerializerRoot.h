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
            /**
             * This function will validate if the root serializer object contains data.
             * A validation with the query is not possible because the query does not contain a data object as root node.
             * The root object of the response must be a "data".
             * @param fieldName The name of the serializer.
             * @return True, if the root object is "data", otherwise false.
             */
            bool wasFieldRequested(std::string fieldName) override;
        public:
            /**
             * C'stor.
             * @param selectionSetOfCurrentLevel The selection set of the current level in the query AST.
             */
            MySerializerRoot(const SelectionSet *selectionSetOfCurrentLevel);

        };
    }
}



#endif //GRAPHQLCPP_MYSERIALIZERROOT_H
