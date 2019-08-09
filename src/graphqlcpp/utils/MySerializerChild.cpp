//
// Created by julian on 12.06.19.
//

#include "../../../include/graphqlcpp/utils/MySerializerChild.h"
#include "../../../include/graphqlparser/AstNode.h"
#include "../../graphqlparser/c/GraphQLAst.h"
#include <cstring>

bool graphqlcpp::utils::MySerializerChild::wasFieldRequested(std::string fieldName) {
    const std::vector<std::unique_ptr<Selection>> &selectionSetArray =
            this->selectionSetOfCurrentLevel->getSelections();

    //a separate counter variable because the counter variable i of the for-loop is of type pointer.
    for (const auto & element : selectionSetArray) {

        //get the pointer to the field on place index in the list/array of Selections.
        // The field is a node of the AST.
        const GraphQLAstField *graphQlField =
                (GraphQLAstField *) element.get();
        const Field *field = (const Field *) graphQlField;

        const Name *namePointer = &field->getName();
        const char *name = namePointer->getValue();
        if(fieldName.compare(name) == 0) {
            this->selectionSetNextLevelOfCurrentField = field->getSelectionSet();
            return true;
        }
    }
    return false;
}

graphqlcpp::utils::MySerializerChild::MySerializerChild(
        const facebook::graphql::ast::SelectionSet *selectionSetOfCurrentLevel) : MySerializer(
        selectionSetOfCurrentLevel){
}
