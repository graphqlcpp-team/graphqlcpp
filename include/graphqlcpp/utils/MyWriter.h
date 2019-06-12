//
// Created by julian on 07.04.19.
//

#ifndef GRAPHQLCPP_MYWRITER_H
#define GRAPHQLCPP_MYWRITER_H

#include <string>
#include <vector>

using namespace std;

namespace graphqlcpp {
    namespace utils {
        using namespace std;

        class MyWriter {
        private:
            string data;

            void removeLastChar();

        public:
            MyWriter();

            void appendValue(char *name, int val);

            void appendValue(char *name, char *val);

            void appendValue(char *name, bool val);

            void appendValue(char *name, MyWriter *writer);

            void appendValue(char *name, vector<int> values);

            void appendValue(char *name, vector<string> values);

            void appendValue(char *name, vector<bool> values);

            void appendValue(char *name, vector<MyWriter*> writers);

            string getJson();

        };
    }
}


#endif //GRAPHQLCPP_MYWRITER_H
