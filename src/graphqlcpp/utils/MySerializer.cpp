//
// Created by julian on 05.04.19.
//

#include "../../../include/graphqlcpp/utils/MySerializer.h"

namespace graphqlcpp {
    namespace utils {
        bool MySerializer::wasFieldRequested(char *fieldName) {
            //TODO check in ast node if requested
            return true;
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

        void MySerializer::setVal(char *name, IGraphQlDTO *val) {
            if (wasFieldRequested(name)) {
                //TODO die zeile muss angepasst werden
                SelectionSet *childLevelSelectionSet = this->selectionSetOfCurrentLevel;

                MySerializer *childNodeSerializer = new MySerializer(childLevelSelectionSet);
                childNodeSerializer = val->serialize(childNodeSerializer);
                this->writer->appendValue(name, childNodeSerializer->createJson());
                delete childNodeSerializer;
            }
        }

        MyWriter *MySerializer::createJson() {
            return this->writer;
        }

        MySerializer::MySerializer(SelectionSet *selectionSetOfCurrentLevel) {
            this->selectionSetOfCurrentLevel = selectionSetOfCurrentLevel;
            this->writer = new MyWriter();
        }

        MySerializer::~MySerializer() {
            delete writer;
        }
    }
}




