//
// Created by julian on 07.04.19.
//

#ifndef GRAPHQLCPP_MYWRITER_H
#define GRAPHQLCPP_MYWRITER_H

#include <string>

namespace graphqlcpp {
    namespace utils {
        using namespace std;

        class MyWriter {
        private:
            string data;
        public:
            MyWriter();

            void appendValue(char *name, int val);

            void appendValue(char *name, char *val);

            void appendValue(char *name, bool val);

            void appendValue(char *name, MyWriter *writer);

            string getJson();
        };
    }
}


#endif //GRAPHQLCPP_MYWRITER_H
