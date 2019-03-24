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

        /**
         * Constructor of the class schemaAstNode.          *
         * @param schemaAstRootNode The root node of the schema AST.
         */
        SchemaAstWraper::SchemaAstWraper(Node *schemaAstRootNode) {
            this->schema = schemaAstRootNode;
        }

        /**
         * This method convert the schema AST to the json format.
         * @return The schema as a JSON string.
         * @throw NoSchemaSetException if no schema was set.
         */
        const char *SchemaAstWraper::printSchemaAsJson() {
            if (schema != nullptr) {
                const char *json = graphql_ast_to_json(
                        (const struct GraphQLAstNode *) schema);
                return json;
            }
            throw NoSchemaSetException();
        }

        /**
         * This method checks if the operation is a operation which is set in the schema.
         * Iterates through every operation set in the schema AST. If the transfered operation does not exists
         * in the operation types it is not a valid operation.
         * @param operation The oepration which schould be validate against the schema AST.
         * @return True, if the operation is valid. Otherwise false.
         */
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

        /**
         * This method gets the schema definition of the schema.
         * The schema definition is necessary to get the operation set in the schema.
         * The schema AST is an array and the first element is a schema definition.
         * @return The schema definition of the schema AST.
         */
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

        /**
         * This method gets the document. This is the root element of the schema AST.
         * @return The document.
         */
        const Document *SchemaAstWraper::getDocument() {
            if (schema != nullptr) {
                const GraphQLAstDocument *graphQlAstDocument = (const struct GraphQLAstDocument *) this->schema;
                const Document *document = (const Document *) graphQlAstDocument;
                return document;
            }
            throw NoSchemaSetException();
        }

        /**
         * This method validate if a node exists as the child of the root node.
         * Must make a difference whether the father node is the operation or not. That's because the types of the
         * nodes differ.
         * First the field name is searched in the fields. If the name was found, the node name is extracted out of
         * the AST. This name can be searched in the other nodes, if a field with this name exists. If this is the
         * case the child field name exists as a child of the father node.
         * @param childFieldName The name of the child field.
         * @param fatherFieldName The name of the father field.
         * @return True, if the node exists as child ot the father node.
         */
        bool SchemaAstWraper::nodeExistsAsChildOf(const char *childFieldName, const char *fatherFieldName) {

            cout << childFieldName << endl;
            cout << fatherFieldName << endl;

            const std::vector<std::unique_ptr<Definition>> &operationDefintion = getDocument()->getDefinitions();
            const char *fatherNodeName = nullptr;

            if (strcmp(fatherFieldName, "query") == 0 || strcmp(fatherFieldName, "mutation") == 0) {
                //Special treatment if father element is the operation,
                // because the structure of this part of the AST differs

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
                            const Type *type = &fields[indexFields].get()->getType();
                            const NamedType *namedType = (NamedType *) type;
                            fatherNodeName = namedType->getName().getValue();
                            break;
                            //const Name* name = &namedType->getName();

                        }
                        indexFields++;
                    }
                    if (fatherNodeName != nullptr) {
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

        bool SchemaAstWraper::isArgumentValid(const char *name, const Value *value, const char *fieldName) {

            const std::vector<std::unique_ptr<Definition>> &operationDefintion = getDocument()->getDefinitions();
            const char *fatherNodeName = nullptr;

            if (strcmp(fieldName, "query") == 0 || strcmp(fieldName, "mutation") == 0) {
                //TODO throw exception: it is not allowed here to have arguments
                return false;
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

                        const char *fieldNameLoop = fields[indexFields].get()->getName().getValue();

                        if (strcmp(fieldNameLoop, fieldName) == 0) {
                            const vector<unique_ptr<InputValueDefinition>> *arguments;
                            arguments = fields[indexFields].get()->getArguments();
                            return iterateThroughArgumentsAndValidate(arguments, name, value);
                        }
                        indexFields++;
                    }
                    index++;
                }
            }
            return false;
        }

        bool SchemaAstWraper::iterateThroughArgumentsAndValidate(
                const std::vector<std::unique_ptr<facebook::graphql::ast::InputValueDefinition>> *arguments,
                const char *argumentName, const Value *value) {
            int indexArguments = 0;
            for (auto j = arguments->begin(); j != arguments->end(); ++j) {
                const unique_ptr<InputValueDefinition> *argument = arguments[indexArguments].data();

                //const GraphQLAstInputValueDefinition* graphQLAstInputValueDefinition =
                //      (const GraphQLAstInputValueDefinition*) argument;
                const char *argumentNameLoop = argument->get()->getName().getValue();
                //const InputValueDefinition* inputValueDefinition =
                //     (const InputValueDefinition*) argument;
                //const char* argumentNameLoop = inputValueDefinition->getName().getValue();
                if (strcmp(argumentNameLoop, argumentName) == 0) {
                    //find argument with name
                    //now have to check the type and then convert the value
                    return validateArgument(argument, value);
                }
            }
            return false;
        }

        bool SchemaAstWraper::validateArgument(const std::unique_ptr<InputValueDefinition> *argument,
                                               const facebook::graphql::ast::Value *value) {
            const Type &type = argument->get()->getType();
            const NonNullType &nonNullType = (const NonNullType &) type;
            const NamedType &nam = (NamedType &) nonNullType.getType();

            const char *valueType = nam.getName().getValue();
            //const Type* typePointer = &type;
            //const NamedType *namedType = (NamedType *) typePointer;
            //const Name * nameType = &namedType->getName();
            //const char * valueType = nameType->getValue();

            if (strcmp(valueType, "ID") == 0 || strcmp(valueType, "String") == 0 || strcmp(valueType, "string") == 0) {
                try {
                    const StringValue *castedValue = (StringValue *) value;
                    const char * valueOfArgument = castedValue->getValue();
                }
                catch (...) {
                    return false;
                }

            } else if (strcmp(valueType, "int") == 0 || strcmp(valueType, "Int") == 0) {
                try {
                    const IntValue *intValue = (IntValue *) value;
                    const char * argumentsValue = intValue->getValue();
                    for(auto i = 0; argumentsValue[i]!= '\0'; i++) {
                        if(argumentsValue[i] < '0' || argumentsValue[i] > '9')
                            return false;
                    }
                }
                catch (...) {
                    return false;
                }
            } else if (strcmp(valueType, "Float") == 0 || strcmp(valueType, "float") == 0) {
                try {
                    const FloatValue *floatValue = (FloatValue *) value;
                    const char * argumentsValue = floatValue->getValue();
                    bool pointWasThere = false;
                    for(auto i = 0; argumentsValue[i]!= '\0'; i++) {
                        if(argumentsValue[i] == '.' && !pointWasThere) {
                            pointWasThere = true;
                            continue;
                        }
                        if(argumentsValue[i] < '0' || argumentsValue[i] > '9' ||
                        (argumentsValue[i] == '.' && pointWasThere))
                            return false;

                    }
                }
                catch (...) {
                    return false;
                }
            } else if(strcmp(valueType, "Boolean") == 0 || strcmp(valueType, "boolean") == 0) {
                try {
                    const StringValue * booleanValue = (StringValue *) value;
                    const char* argumentsValue = booleanValue->getValue();
                    if(((int*)&argumentsValue[0]) == (int*)0x1 || ((int*)&argumentsValue[0]) == (int*)0x0)
                        return true;
                    return false;
                }
                catch(...) {
                    return false;
                }
            }
            return true;
        }
    } /* namespace validators */
} /* namespace graphqlcpp */

