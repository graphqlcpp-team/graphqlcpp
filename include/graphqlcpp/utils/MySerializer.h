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
            bool wasFieldRequested(char *fieldName);

            MyWriter *writer;
            const SelectionSet *selectionSetOfCurrentLevel;
            const SelectionSet *selectionSetNextLevelOfCurrentField;
        public:
            MySerializer(const SelectionSet *selectionSetOfCurrentLevel);

            virtual ~MySerializer();

            void setVal(char *name, int val);

            void setVal(char *name, char *val);

            void setVal(char *name, bool val);

            void setVal(char *name, IGraphQlDTO *val);

            void setVal(char *name, vector<int> values);

            void setVal(char *name, vector<string> values);

            void setVal(char *name, vector<bool> values);

            void setVectorWritersVal(char *name, vector<MyWriter*> writers);

            MyWriter *createJson();
        };
    }
}


#endif //MYSERIALIZER_H_
