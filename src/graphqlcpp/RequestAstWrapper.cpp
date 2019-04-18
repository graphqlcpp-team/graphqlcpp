//
// Created by amelie on 16.04.19.
//

#include "../../include/graphqlcpp/RequestAstWrapper.h"

std::string graphqlcpp::RequestAstWrapper::extractOperation() {
    return std::__cxx11::string();
}

graphqlcpp::ResolverInfo *graphqlcpp::RequestAstWrapper::extractResolver() {
    return nullptr;
}

facebook::graphql::ast::SelectionSet *graphqlcpp::RequestAstWrapper::extractSelectionSetForSerialisation() {
    return nullptr;
}
