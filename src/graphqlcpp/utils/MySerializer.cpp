//
// Created by julian on 05.04.19.
//

#include "../../../include/graphqlcpp/utils/MySerializer.h"
#include "../../../include/graphqlcpp/utils/MySerializerChild.h"

#include <cstring>


namespace graphqlcpp {
    namespace utils {
        void MySerializer::setVal(std::string name, int val) {
            if (wasFieldRequested(name)) {
                this->writer->appendValue(name, val);
            }
        }

        void MySerializer::setVal(std::string name, std::string val) {
            if (wasFieldRequested(name)) {
                this->writer->appendValue(name, val);
            }
        }

        void MySerializer::setVal(std::string name, bool val) {
            if (wasFieldRequested(name)) {
                this->writer->appendValue(name, val);
            }
        }

        void MySerializer::setVal(std::string name, vector<int> values){
            if (wasFieldRequested(name)) {
                this->writer->appendValue(name, values);
            }
        }

        void MySerializer::setVal(std::string name, vector<string> values){
            if (wasFieldRequested(name)) {
                this->writer->appendValue(name, values);
            }
        }

        void MySerializer::setVal(std::string name, vector<bool> values){
            if (wasFieldRequested(name)) {
                this->writer->appendValue(name, values);
            }
        }

        void MySerializer::setVal(std::string name, vector<IGraphQlDTO*> val){
            if (wasFieldRequested(name)) {
                vector<MyWriter*> writerVec = vector<MyWriter*>(val.size());
                const SelectionSet *childLevelSelectionSet = this->selectionSetNextLevelOfCurrentField;
                for(int i =0; i<val.size(); i++){
                    MySerializer *childNodeSerializer = new MySerializerChild(childLevelSelectionSet);
                    childNodeSerializer = val.at(i)->serialize(childNodeSerializer);
                    writerVec[i] = childNodeSerializer->createJson();
                }

                this->writer->appendVectorWritersValue(name, writerVec);
            }
        }

        void MySerializer::setVal(std::string name, IGraphQlDTO *val) {
            if (wasFieldRequested(name)) {
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




