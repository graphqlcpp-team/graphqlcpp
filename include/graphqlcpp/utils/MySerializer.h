//
// Created by julian on 05.04.19.
//

#ifndef MYSERIALIZER_H_
#define MYSERIALIZER_H_

#include "../IGraphQlDTO.h"
#include "../../graphqlparser/AstNode.h"
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
        private:
            bool wasFieldRequested(std::string fieldName);

            MyWriter *writer;
            const SelectionSet *selectionSetOfCurrentLevel;
            const SelectionSet *selectionSetNextLevelOfCurrentField;
        public:
            MySerializer(const SelectionSet *selectionSetOfCurrentLevel);

            virtual ~MySerializer();

            void setVal(std::string name, int val);

            void setVal(std::string name, std::string val);

            void setVal(std::string name, bool val);

            void setVal(std::string name, IGraphQlDTO *val);

            void setVal(std::string name, vector<int> values);

            void setVal(std::string name, vector<string> values);

            void setVal(std::string name, vector<bool> values);

            void setVectorWritersVal(std::string name, vector<MyWriter*> writers);

            MyWriter *createJson();
        };
    }
}


#endif //MYSERIALIZER_H_
