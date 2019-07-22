//
// Created by julian on 05.04.19.
//

#ifndef MYSERIALIZER_H_
#define MYSERIALIZER_H_

#include "../IGraphQlDTO.h"
#include "../../graphqlparser/Ast.h"
#include "MyWriter.h"

namespace graphqlcpp {
    namespace api {
        class IGraphQlDTO;
    }
    namespace utils {
        using namespace facebook::graphql::ast;
        using namespace graphqlcpp::api;

        class MySerializer {
        protected:
        public:
            /**
             * D'stor.
             */
            virtual ~MySerializer();
        protected:
            /**
             * Instance of MyWriter. MyWrtier is the wrapper class for the creation of the JSON element.
             */
            MyWriter *writer;

            /**
             * This function will validate if the resolver field is requested.
             * @param fieldName The name of the field in the resolver.
             * @return true, if field was requested, otherwise false.
             */
            virtual bool wasFieldRequested(std::string fieldName)=0;

            /**
             * A pointer to the current level in the queryAST
             */
            const SelectionSet *selectionSetOfCurrentLevel;

            /**
             * A pointer to the next level in the queryAST.
             */
            const SelectionSet *selectionSetNextLevelOfCurrentField;

            /**
             * C'stor.
             * @param selectionSetOfCurrentLevel The selection set of the current level in the query AST.
             */
            MySerializer(const SelectionSet *selectionSetOfCurrentLevel);
        public:
            /**
             * This function will call the writer function to add a value to the JSON object.
             * A Integer value will be added.
             * @param name The key name of JSON element.
             * @param val The value of JSON element. (int)
             */
            void setVal(std::string name, int val);

            /**
             * This function will call the writer function to add a value to the JSON object.
             * A string value will be added.
             * @param name The key name of JSON element.
             * @param val The value of JSON element. (string)
             */
            void setVal(std::string name, std::string val);

            /**
             * This function will call the writer function to add a value to the JSON object.
             * A boolean value will be added.
             * @param name The key name of JSON element.
             * @param val The value of JSON element. (bool)
             */
            void setVal(std::string name, bool val);

            /**
             * This function will call the writer function to add a value to the JSON object.
             * A boolean value will be added.
             * @param name The key name of JSON element.
             * @param val The value of JSON element. (float)
             */
            void setVal(std::string name, float val);

            /**
             * This function will call the writer function to add a value to the JSON object.
             * A IGraphQLDTO value will be added. This meens a nested JSON element will be added.
             * @param name The key name of JSON element.
             * @param val The value of JSON element. (nested element - IGraphQlDTO)
             */
            void setVal(std::string name, IGraphQlDTO *val);

            /**
             * This function will call the writer function to add a value to the JSON object.
             * An array of ints as value will be added.
             * @param name The key name of JSON element.
             * @param values The value of JSON element. (array of ints)
             */
            void setVal(std::string name, vector<int> values);

            /**
             * This function will call the writer function to add a value to the JSON object.
             * An array of strings as value will be added.
             * @param name The key name of JSON element.
             * @param values The value of JSON element. (array of strings)
             */
            void setVal(std::string name, vector<string> values);

            /**
             * This function will call the writer function to add a value to the JSON object.
             * An array of booleans as value will be added.
             * @param name The key name of JSON element.
             * @param values The value of JSON element. (array of bools)
             */
            void setVal(std::string name, vector<bool> values);

            /**
             * This function will call the writer function to add a value to the JSON object.
             * An array of nested JSON elements as value will be added.
             * @param name The key name of JSON element.
             * @param val The value of JSON element. (array of nested JSON elements - IGraphQlDTO)
             */
            void setVal(std::string name, vector<IGraphQlDTO*> val);

            /**
             * This will create a MyWriter object, where the JSON element will be created.
             * @return A object of MyWriter.
             */
            MyWriter *createJson();
        };
    }
}


#endif //MYSERIALIZER_H_
