//
// Created by julian on 05.04.19.
//

#include "../../../include/graphqlcpp/utils/MySerializer.h"
#include "../../graphqlparser/c/GraphQLAst.h"
#include <cstring>


namespace graphqlcpp {
    namespace utils {
        bool MySerializer::wasFieldRequested(char *fieldName) {

            const std::vector<std::unique_ptr<Selection>> &selectionSetArray =
                    this->selectionSetOfCurrentLevel->getSelections();

            //a separate counter variable because the counter variable i of the for-loop is of type pointer.
            int index = 0;
            for (auto i = selectionSetArray.begin(); i != selectionSetArray.end();
                 ++i) {

                //get the pointer to the field on place index in the list/array of Selections.
                // The field is a node of the AST.
                const GraphQLAstField *graphQlField =
                        (GraphQLAstField *) selectionSetArray[index].get();
                const Field *field = (const Field *) graphQlField;
                const Name *namePointer = &field->getName();
                const char *name = namePointer->getValue();
                if(strcmp(name, fieldName) == 0) {
                    this->selectionSetNextLevelOfCurrentField = field->getSelectionSet();
                    return true;
                }
                index ++;
            }
            return false;
        }

        void MySerializer::setVal(char *name, int val) {
            if (wasFieldRequested(name)) {
                this->writer->appendValue(name, val);
            }
        }

        void MySerializer::setVal(char *name, char *val) {
            if (wasFieldRequested(name)) {
                this->writer->appendValue(name, val);
            }
        }

        void MySerializer::setVal(char *name, bool val) {
            if (wasFieldRequested(name)) {
                this->writer->appendValue(name, val);
            }
        }

        void MySerializer::appendValue(char *name, vector<int> values){
            if (wasFieldRequested(name)) {
                this->writer->appendValue(name, values);
            }
        }

        void MySerializer::appendValue(char *name, vector<string> values){
            if (wasFieldRequested(name)) {
                this->writer->appendValue(name, values);
            }
        }

        void MySerializer::appendValue(char *name, vector<bool> values){
            if (wasFieldRequested(name)) {
                this->writer->appendValue(name, values);
            }
        }

        void MySerializer::appendVectorWritersValue(char *name, vector<MyWriter*> writers){
            if (wasFieldRequested(name)) {
                this->writer->appendVectorWritersValue(name, writers);
            }
        }

        void MySerializer::setVal(char *name, IGraphQlDTO *val) {
            if (wasFieldRequested(name)) {
                //TODO die zeile muss angepasst werden
                const SelectionSet *childLevelSelectionSet = this->selectionSetNextLevelOfCurrentField;

                MySerializer *childNodeSerializer = new MySerializer(childLevelSelectionSet);
                childNodeSerializer = val->serialize(childNodeSerializer);
                this->writer->appendValue(name, childNodeSerializer->createJson());
                delete childNodeSerializer;
            }
        }

        MyWriter *MySerializer::createJson() {
            return this->writer;
        }

        MySerializer::MySerializer(const SelectionSet *selectionSetOfCurrentLevel) {
            this->selectionSetOfCurrentLevel = selectionSetOfCurrentLevel;
            this->writer = new MyWriter();
        }

        MySerializer::~MySerializer() {
            delete writer;
        }
    }
}




