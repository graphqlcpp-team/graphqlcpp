/*
 * SchemaAstWraper.cpp
 *
 *  Created on: 17.02.2019
 *      Author: julian2
 */

#include "SchemaAstWraper.h"
#include "../../libgraphqlparser/c/GraphQLAstToJSON.h"
#include "../../libgraphqlparser/Ast.h"
#include "../../libgraphqlparser/c/GraphQLAst.h"
#include "../exceptions/NoSchemaSetException.h"
#include <cstring>


namespace graphqlcpp {
    namespace validators {

        using namespace facebook::graphql;
        using namespace graphqlcpp::exceptions;
        using namespace std;
        using namespace facebook::graphql::ast;

        SchemaAstWraper::SchemaAstWraper(Node *schemaAstRootNode) {
            this->schema = schemaAstRootNode;
        }

        const char *SchemaAstWraper::printSchemaAsJson() {
            if (schema != nullptr) {
                const char *json = graphql_ast_to_json(
                        (const struct GraphQLAstNode *) schema);
                return json;
            }
            throw NoSchemaSetException();
        }

        bool SchemaAstWraper::isOperationValid(const char *operation) {
            const SchemaDefinition *schemaDefinition = getSchemaDefinition();
            const vector<unique_ptr<OperationTypeDefinition>> &operationTypes = schemaDefinition->getOperationTypes();

            int index = 0;
            for (auto j = operationTypes.begin(); j != operationTypes.end(); ++j) {
                const char *operationTyp = operationTypes[index].get()->getOperation();
                if (strcmp(operation, operationTyp) == 0) {
                    return true;
                }
                index++;
            }

            return false;
        }

        const SchemaDefinition *SchemaAstWraper::getSchemaDefinition() {
            const std::vector<std::unique_ptr<Definition>> &operationDefintion = getDocument()->getDefinitions();
            std::unique_ptr<Definition, default_delete<Definition>>::pointer schemaDefinitioNotCasted =
                    operationDefintion[0].get();
            const GraphQLAstSchemaDefinition *schemaDefinitionCasted =
                    (const GraphQLAstSchemaDefinition *) schemaDefinitioNotCasted;
            const SchemaDefinition *schemaDefinition =
                    (const SchemaDefinition *) schemaDefinitionCasted;
            return schemaDefinition;

        }

        const Document *SchemaAstWraper::getDocument() {
            const GraphQLAstDocument *graphQlAstDocument = (const struct GraphQLAstDocument *) this->schema;
            const Document *document = (const Document *) graphQlAstDocument;
            return document;
        }

        /*const std::vector<std::unique_ptr<Definition>> SchemaAstWraper::getOperationDefinition() {
            const GraphQLAstDocument *graphQlAstDocument = (const struct GraphQLAstDocument *) this->schema;
            const Document *document = (const Document *) graphQlAstDocument;
            const std::vector<std::unique_ptr<Definition>> &operationDefintion = document->getDefinitions();
            return operationDefintion;
        }*/


        bool SchemaAstWraper::nodeExsitstsAsChildOf(const char *childFieldName, const char *fatherFieldName) {

            cout << childFieldName << endl;
            cout << fatherFieldName << endl;

            const std::vector<std::unique_ptr<Definition>> &operationDefintion = getDocument()->getDefinitions();
            const char *fatherNodeName = nullptr;

            if (strcmp(fatherFieldName, "query") == 0 || strcmp(fatherFieldName, "mutation") == 0) {
                //Special treatement if father element is the operation, because the structure of this part of the AST differs

                const SchemaDefinition *schemaDefinition = getSchemaDefinition();
                const vector<unique_ptr<OperationTypeDefinition>> &operationTypes = schemaDefinition->getOperationTypes();

                int index = 0;
                for (auto j = operationTypes.begin(); j != operationTypes.end(); ++j) {
                    const char *operationTyp = operationTypes[index].get()->getOperation();
                    if (strcmp(fatherFieldName, operationTyp) == 0) {
                        fatherNodeName = operationTypes[index].get()->getType().getName().getValue();
                        break;
                    }
                    index++;
                }
                if (fatherNodeName == nullptr) {
                    //thow some exception, this part of code should never be reached!!!
                    return false;
                }
            } else {
                //serch father node in normal case
                int index = 1;
                for (auto j = operationDefintion.begin() + 1; j != operationDefintion.end(); ++j) {
                    auto operationDefinition = operationDefintion[index].get();
                    const GraphQLAstObjectTypeDefinition *graphQLAstObjectTypeDefinition =
                            (const GraphQLAstObjectTypeDefinition *) operationDefinition;
                    const ObjectTypeDefinition *objectTypeDefinition =
                            (const ObjectTypeDefinition *) graphQLAstObjectTypeDefinition;
                    const vector<unique_ptr<FieldDefinition>> &fields = objectTypeDefinition->getFields();

                    int indexFields = 0;
                    for (auto i = fields.begin(); i != fields.end(); ++i) {
                        const char *fieldName = fields[indexFields].get()->getName().getValue();
                        if (strcmp(fatherFieldName, fieldName) == 0) {
                            //fields[indexFields].get()->getType()
                            //const GraphQLAstNamedType* graphQLAstType = (GraphQLAstNamedType*) fields[indexFields].get();
                            //const NamedType* namedType = (const NamedType*) graphQLAstType;
                            const Type *type = &fields[indexFields].get()->getType();
                            const NamedType *namedType = (NamedType *) type;
                            fatherNodeName = namedType->getName().getValue();
                            break;
                            //const Name* name = &namedType->getName();

                        }
                        indexFields++;
                    }
                    if(fatherNodeName != nullptr) {
                        break;
                    }
                    index++;
                }
                if (fatherNodeName == nullptr) {
                    //thow some exception, this part of code should never be reached!!!
                    return false;
                }
            }

            //now the father node name as it is set in the Schema is known and can be compared to other AST nodes

            int index = 1;
            for (auto j = operationDefintion.begin() + 1; j != operationDefintion.end(); ++j) {
                auto operationDefinition = operationDefintion[index].get();
                const GraphQLAstObjectTypeDefinition *graphQLAstObjectTypeDefinition =
                        (const GraphQLAstObjectTypeDefinition *) operationDefinition;
                const ObjectTypeDefinition *objectTypeDefinition =
                        (const ObjectTypeDefinition *) graphQLAstObjectTypeDefinition;
                const char *typeDefinitionName = objectTypeDefinition->getName().getValue();

                if (strcmp(typeDefinitionName, fatherNodeName) == 0) {
                    //in this AST node the child node must be located

                    const vector<unique_ptr<FieldDefinition>> &fields = objectTypeDefinition->getFields();

                    int indexFields = 0;
                    for (auto i = fields.begin(); i != fields.end(); ++i) {
                        const char *fieldName = fields[indexFields].get()->getName().getValue();
                        if (strcmp(childFieldName, fieldName) == 0) {
                            //the child node exists as node of father node
                            return true;
                        }
                        indexFields++;
                    }
                }

                index++;
            }

            //it does not exists as child of
            return false;
        }

        void iterateThoughAst() {

        }

    } /* namespace validators */
} /* namespace graphqlcpp */

