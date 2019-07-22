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
            /**
             * The JSON element.
             */
            string data;

            /**
             * The last separator (,) will be deleted.
             * This is necessary because after evey method a comma will be added. But after the last value there
             * is no comma needed.
             */
            void replaceLastSeparator();

        public:
            /**
             * C'stor.
             * Will set the first { ot the JSON string.
             */
            MyWriter();

            /**
             * Append a value to the data string in json format. A key with a value will be added.
             * This function will add a int value as value.
             * @param name The key of JSON element.
             * @param val The value of the JSON element. (Int)
             */
            void appendValue(std::string name, int val);

            /**
             * Append a value to the data string in json format. A key with a value will be added.
             * This function will add a string value as value.
             * @param name The key of JSON element.
             * @param val The value of the JSON element. (String)
             */
            void appendValue(std::string name, std::string val);

            /**
             * Append a value to the data string in json format. A key with a value will be added.
             * This function will add a boolean value as value.
             * @param name The key of JSON element.
             * @param val The value of the JSON element. (bool)
             */
            void appendValue(std::string name, bool val);

            /**
             * Append a value to the data string in json format. A key with a value will be added.
             * This function will add a boolean value as value.
             * @param name The key of JSON element.
             * @param val The value of the JSON element. (float)
             */
            void appendValue(std::string name, float val);

            /**
             * Append a value to the data string in json format. A key with a value will be added.
             * This function will add another MyWriter to the JSON. This will look like: key: {...}
             * @param name The key of JSON element.
             * @param writer The other WMyWriter. Its the nested JSON.
             */
            void appendValue(std::string name, MyWriter *writer);

            /**
             * Append a value to the data string in json format. A key with a value will be added.
             * This function will add an array of int values.
             * @param name The key of JSON element.
             * @param values The array of ints.
             */
            void appendValue(std::string name, vector<int> values);

            /**
             * Append a value to the data string in json format. A key with a value will be added.
             * This function will add an array of string values.
             * @param name The key of JSON element.
             * @param values The array of strings.
             */
            void appendValue(std::string name, vector<string> values);

            /**
             * Append a value to the data string in json format. A key with a value will be added.
             * This function will add an array of boolean values.
             * @param name The key of JSON element.
             * @param values The array of boolean.
             */
            void appendValue(std::string name, vector<bool> values);

            /**
             * Append a value to the data string in json format. A key with a value will be added.
             * This function will add an array of nested MyWriter values.
             * @param name The key of JSON element.
             * @param writers The array of nested MyWriter objects.
             */
            void appendVectorWritersValue(std::string name, vector<MyWriter *> writers);

            /**
             * This will return the resulting JSON element. It will add the closing } bracket.
             * @return The resulting JSON element.
             */
            string getJson();

        };
    }
}


#endif //GRAPHQLCPP_MYWRITER_H
