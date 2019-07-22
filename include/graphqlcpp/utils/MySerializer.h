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
            virtual ~MySerializer();
        protected:
            MyWriter *writer;
            virtual bool wasFieldRequested(std::string fieldName)=0;
            const SelectionSet *selectionSetOfCurrentLevel;
            const SelectionSet *selectionSetNextLevelOfCurrentField;
            MySerializer(const SelectionSet *selectionSetOfCurrentLevel);
        public:
            void setVal(std::string name, int val);

            void setVal(std::string name, std::string val);

            void setVal(std::string name, bool val);

            void setVal(std::string name, float val);

            void setVal(std::string name, IGraphQlDTO *val);

            void setVal(std::string name, vector<int> values);

            void setVal(std::string name, vector<string> values);

            void setVal(std::string name, vector<bool> values);

            void setVal(std::string name, vector<IGraphQlDTO*> val);

            MyWriter *createJson();
        };
    }
}


#endif //MYSERIALIZER_H_
