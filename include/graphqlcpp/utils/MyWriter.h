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

            void replaceLastSeparator();

        public:
            MyWriter();

            void appendValue(std::string name, int val);

            void appendValue(std::string name, std::string val);

            void appendValue(std::string name, bool val);

            void appendValue(std::string name, MyWriter *writer);

            void appendValue(std::string name, vector<int> values);

            void appendValue(std::string name, vector<string> values);

            void appendValue(std::string name, vector<bool> values);

            void appendVectorWritersValue(std::string name, vector<MyWriter*> writers);

            string getJson();

        };
    }
}


#endif //GRAPHQLCPP_MYWRITER_H
