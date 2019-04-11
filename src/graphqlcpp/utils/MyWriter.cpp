//
// Created by julian on 07.04.19.
//

#include <vector>
#include "../../../include/graphqlcpp/utils/MyWriter.h"

namespace graphqlcpp {
    namespace utils {
        static const char *const separator = ",";

        MyWriter::MyWriter() {
            this->data = "{";
            //this->data.append("{");
        }

        string MyWriter::getJson() {
            data = data.substr(0, data.length() - 1);
            return data.append("}");
        }

        void MyWriter::replaceLastSeparator() {
            data = data.substr(0, data.length() - 1);
        }


        void MyWriter::appendValue(char *name, int val) {
            data.append("\"");
            data.append(name);
            data.append("\"");
            data.append(":");
            data.append(to_string(val));
            data.append(separator);
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
            data.append(separator);
        }

        void MyWriter::appendValue(char *name, char *val) {
            data.append("\"");
            data.append(name);
            data.append("\"");
            data.append(":");
            data.append("\"");
            data.append(val);
            data.append("\"");
            data.append(separator);
        }

        void MyWriter::appendValue(char *name, MyWriter *writer) {
            data.append("\"");
            data.append(name);
            data.append("\"");
            data.append(":");
            data.append(writer->getJson());
            data.append(separator);
        }


        void MyWriter::appendValue(char *name, vector<int> values) {
            data.append("\"");
            data.append(name);
            data.append("\"");
            data.append(":");
            data.append("[");
            std::string tmpStringRepresentation;
            int index = 0;
            for (auto value = values.begin(); value != values.end(); ++value) {
                tmpStringRepresentation += to_string(values[index]);
                if (value != values.end()) {
                    tmpStringRepresentation += separator;
                }
                index++;
            }
            data.append(tmpStringRepresentation);
            replaceLastSeparator();
            data.append("]");
            data.append(separator);
        }

        void MyWriter::appendValue(char *name, vector<string> values) {
            data.append("\"");
            data.append(name);
            data.append("\"");
            data.append(":");
            data.append("[");
            std::string tmpStringRepresentation;
            int index = 0;
            for (auto value = values.begin(); value != values.end(); ++value) {
                tmpStringRepresentation += "\"" + values[index] + "\"";
                if (value != values.end()) {
                    tmpStringRepresentation += separator;
                }
                index++;
            }
            data.append(tmpStringRepresentation);
            replaceLastSeparator();
            data.append("]");
            data.append(separator);
        }

        void MyWriter::appendValue(char *name, vector<bool> values) {
            string sTrue = "true";
            string sFalse = "false";

            data.append("\"");
            data.append(name);
            data.append("\"");
            data.append(":");
            data.append("[");

            std::string tmpStringRepresentation;
            int index = 0;
            for (auto value = values.begin(); value != values.end(); ++value) {
                if (values[index]) {
                    tmpStringRepresentation += sTrue;
                } else {
                    tmpStringRepresentation += sFalse;
                }


                if (value != values.end()) {
                    tmpStringRepresentation += separator;
                }
                index++;
            }
            data.append(tmpStringRepresentation);
            replaceLastSeparator();
            data.append("]");
            data.append(separator);

        }

        void MyWriter::appendVectorWritersValue(char *name, vector<MyWriter*> writers) {
            string sTrue = "true";
            string sFalse = "false";
            data.append("\"");
            data.append(name);
            data.append("\"");
            data.append(":");
            data.append("[");
            std::string tmpStringRepresentation;
            int index = 0;
            for (auto value = writers.begin(); value != writers.end(); ++value) {
                MyWriter * asdf;
                asdf = writers[index];
                tmpStringRepresentation += writers[index]->getJson();

                if (value != writers.end()) {
                    tmpStringRepresentation += separator;
                }
                index++;
            }
            data.append(tmpStringRepresentation);
            replaceLastSeparator();
            data.append("]");
            data.append(separator);
        }
    }
}