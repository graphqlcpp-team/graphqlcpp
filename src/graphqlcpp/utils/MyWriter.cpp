//
// Created by julian on 07.04.19.
//

#include "../../../include/graphqlcpp/utils/MyWriter.h"

namespace graphqlcpp {
    namespace utils {
        MyWriter::MyWriter() {
            this->data.append("{");
        }

        string MyWriter::getJson() {
            data = data.substr(0, data.length() - 1);
            return data.append("}");
        }


        void MyWriter::appendValue(char *name, int val) {
            data.append("\"");
            data.append(name);
            data.append("\"");
            data.append(":");
            data.append(to_string(val));
            data.append(",");
        }

        void MyWriter::appendValue(char *name, bool val) {
            data.append("\"");
            data.append(name);
            data.append("\"");
            data.append(":");
            if (val) {
                data.append("true");
            } else {
                data.append("false");
            };
            data.append(",");
        }

        void MyWriter::appendValue(char *name, char *val) {
            data.append("\"");
            data.append(name);
            data.append("\"");
            data.append(":");
            data.append("\"");
            data.append(val);
            data.append("\"");
            data.append(",");
        }

        void MyWriter::appendValue(char *name, MyWriter *writer) {
            data.append("\"");
            data.append(name);
            data.append("\"");
            data.append(":");
            data.append(writer->getJson());
            data.append(",");
        }
    }
}