//
// Created by julian on 12.06.19.
//

#include "../../../include/graphqlcpp/utils/MySerializerRoot.h"
#include <cstring>

bool graphqlcpp::utils::MySerializerRoot::wasFieldRequested(char *fieldName) {
    return strcmp("data",fieldName)==0;
}

graphqlcpp::utils::MySerializerRoot::MySerializerRoot(
        const facebook::graphql::ast::SelectionSet *selectionSetOfCurrentLevel) : MySerializer(
        selectionSetOfCurrentLevel) {
    this->selectionSetNextLevelOfCurrentField = selectionSetOfCurrentLevel;
}
