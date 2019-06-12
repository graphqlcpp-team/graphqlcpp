//
// Created by julian on 05.04.19.
//

#include "../../../include/graphqlcpp/utils/MySerializer.h"
#include "../../../include/graphqlcpp/utils/MySerializerChild.h"

#include <cstring>


namespace graphqlcpp {
    namespace utils {
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

        void MySerializer::setVal(char *name, vector<int> values){
            if (wasFieldRequested(name)) {
                this->writer->appendValue(name, values);
            }
        }

        void MySerializer::setVal(char *name, vector<string> values){
            if (wasFieldRequested(name)) {
                this->writer->appendValue(name, values);
            }
        }

        void MySerializer::setVal(char *name, vector<bool> values){
            if (wasFieldRequested(name)) {
                this->writer->appendValue(name, values);
            }
        }

        void MySerializer::setVal(char *name, vector<IGraphQlDTO*> val){
            if (wasFieldRequested(name)) {
                vector<MyWriter*> writerVec = vector<MyWriter*>(val.size());
                const SelectionSet *childLevelSelectionSet = this->selectionSetNextLevelOfCurrentField;
                for(auto v : val){

                    MySerializer *childNodeSerializer = new MySerializerChild(childLevelSelectionSet);
                    childNodeSerializer = v->serialize(childNodeSerializer);
                    writerVec.push_back(childNodeSerializer->createJson());
                }

                this->writer->appendValue(name, writerVec);
            }
        }

        void MySerializer::setVal(char *name, IGraphQlDTO *val) {
            if (wasFieldRequested(name)) {
                //TODO die zeile muss angepasst werden
                const SelectionSet *childLevelSelectionSet = this->selectionSetNextLevelOfCurrentField;

                MySerializer *childNodeSerializer = new MySerializerChild(childLevelSelectionSet);
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




