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
            virtual bool wasFieldRequested(char *fieldName)=0;
            const SelectionSet *selectionSetOfCurrentLevel;
            const SelectionSet *selectionSetNextLevelOfCurrentField;
            MySerializer(const SelectionSet *selectionSetOfCurrentLevel);
        public:
            void setVal(char *name, int val);

            void setVal(char *name, char *val);

            void setVal(char *name, bool val);

            void setVal(char *name, IGraphQlDTO *val);

            void setVal(char *name, vector<int> val);

            void setVal(char *name, vector<string> val);

            void setVal(char *name, vector<bool> val);

            void setVal(char *name, vector<IGraphQlDTO*> val);

            MyWriter *createJson();
        };
    }
}


#endif //MYSERIALIZER_H_
