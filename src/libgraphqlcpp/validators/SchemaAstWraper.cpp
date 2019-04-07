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
#include "../exceptions/ArgumentNotValidException.h"
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
         * @throw NoSchemaSetException if the schema is not set.
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

            const std::vector<std::unique_ptr<Definition>> &operationDefintion = getDocument()->getDefinitions();
            const char *fatherNodeName = nullptr;

            if (strcmp(fatherFieldName, "query") == 0 || strcmp(fatherFieldName, "mutation") == 0) {
                fatherNodeName = getFatherFieldNameIfFatherIsOperatiom(fatherFieldName);
                if (fatherNodeName == nullptr) {
                    //this part of code should never be reached!!!
                    return false;
                }
            } else {
                fatherNodeName = getFatherNodeNameIfFatherIsNotOperation(fatherFieldName, operationDefintion);
                if (fatherNodeName == nullptr) {
                    //this part of code should never be reached!!!
                    return false;
                }
            }

            //now the father node name as it is set in the Schema is known and can be compared to other AST nodes

            bool fieldExistsAsChild = fieldExistsAsChildOfFatherNode(childFieldName, operationDefintion, fatherNodeName);
            if(fieldExistsAsChild)
                return true;

            //it does not exists as child of
            return false;
        }

        /**
         * It's conna be check if the field name of the child from the query exists as a child of the node.
         * Therefor there is an iteration through the child fields of the father node set in the query.
         * To get to the father node there is a iteration through the AST necessary, this is the first for-loop.
         * If we have the father node we can iterate thorugh its fields (the second for-loop).
         * If a child node with the name of the child name set in the query is there, the function returns true.
         * @param childFieldName The child field name set in the query. This is exactly the name as in the query.
         * @param operationDefintion The start point of the schema AST.
         * @param fatherNodeName The father node name. This has to be extracted out of the AST.
         * @return True if the field exists as child of the father node, otherwise false.
         */
        bool SchemaAstWraper::fieldExistsAsChildOfFatherNode(const char *childFieldName,
                                                             const std::vector<std::unique_ptr<facebook::graphql::ast::Definition>> &operationDefintion,
                                                             const char *fatherNodeName) {
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
            return false;
        }

        /**
         * This function will get the fathers node name from the field name.
         * This function should be called if the father node name is not an operation as query or mutation.
         * It is necessary to get the node name to find the father node in the AST. It is not possible to get the fathers
         * node with only the field name. The fathers node is necessary to get the child fields.
         * @param fatherFieldName The name of the father field as set in the query. This is exactly the name as in the query.
         * @param operationDefintion The start point of the schema AST.
         * @return The father node name.
         */
        const char * SchemaAstWraper::getFatherNodeNameIfFatherIsNotOperation(const char *fatherFieldName,
                const std::vector<std::unique_ptr<facebook::graphql::ast::Definition>> &operationDefintion) {
            int index = 1;
            const char* fatherNodeName = nullptr;
            //begin with 1 because the first element is the operation and is treated seperatly.
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
                return fatherNodeName;
        }

        /**
         * This function will get the fathers node name from the field name.
         * This function should be called if the father node name is  an operation as query or mutation.
         * There is a special treatment if the father field is an operation. This is because the structure of this
         * part of the schema AST differs to the rest.
         * It is necessary to get the node name to find the father node in the AST. It is not possible to get the fathers
         * node with only the field name. The fathers node is necessary to get the child fields.
         * @param fatherFieldName The name of the father field as set in the query. This is exactly the name as in the query.
         * @return The father node name.
         */
        const char *SchemaAstWraper::getFatherFieldNameIfFatherIsOperatiom(const char *fatherFieldName) {

            const char *fatherNodeName;
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
            return fatherNodeName;
        }

        /**
         * This function validates if the argument is valid.
         * To get the arguments of the field it is necessary to get the field node. Therefor the for-loop iterates
         * through the schema AST (for loop). The start index is not the first node because this is the operation
         * node and at this there can't be a argument set.
         * After having the field node the list of all arguments will be transfered to the function which validates
         * the argument against a list of arguments.
         * @param name The name of the argument. In the query it's the part in brackets in front of the equal sign.
         * @param value The value of the argument. In the query it's the part in brackets behind the equal sign.
         * @param fieldName The name of the field to which the argument will be executed.
         * @return True if the argument is valid, otherwise false.
         */
        bool SchemaAstWraper::isArgumentValid(const char *name, const Value *value, const char *fieldName) {

            const std::vector<std::unique_ptr<Definition>> &operationDefintion = getDocument()->getDefinitions();

            if (strcmp(fieldName, "query") == 0 || strcmp(fieldName, "mutation") == 0) {
                return false;
            } else {
                //search father node in normal case
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

        /**
         * Iterate through each argument of a field an check if the name of the argument is the same as in the query.
         * If the name equals the function to validate the value of the argument will be called.
         * @param arguments The list of the arguments of the field.
         * @param argumentName The name of the argument set in the query. This is exactly the name as in the query.
         * @param value The value of the argument set in the query.
         * @return True if the argument exists and has the rigth type of value otherwise false.
         */
        bool SchemaAstWraper::iterateThroughArgumentsAndValidate(
                const std::vector<std::unique_ptr<facebook::graphql::ast::InputValueDefinition>> *arguments,
                const char *argumentName, const Value *value) {
            int indexArguments = 0;
            for (auto j = arguments->begin(); j != arguments->end(); ++j) {
                const unique_ptr<InputValueDefinition> *argument = arguments[indexArguments].data();

                const char *argumentNameLoop = argument->get()->getName().getValue();
                if (strcmp(argumentNameLoop, argumentName) == 0) {
                    //find argument with name
                    //now have to check the type and then convert the value
                    return validateArgument(argument, value);
                }
            }
            return false;
        }

        /**
         * This function validates if the value of the argument has the right data type.
         * The data type which the argument should have is taken from the schema AST.
         * For each data type there is a seperate check. That's because in the query AST no data type is saved and
         * most of the values are in the format string. Therefor int and float values are validate with an iteration
         * through the string.
         * The exception is the type boolean, the AST structure differs here. We can check if the argument is in the
         * query of type boolean by checking the AST structure. In this case the query AST does not contains a pointer
         * to the argument value, it only has the value itself at this part of the AST. By checking if there is a
         * pointer or the value it is possible to check the data type.
         * @param argument The pointer to the argument in the schema AST.
         * @param value The pointer to the value of the query in the query AST.
         * @return True, if the data type of the argument is as expected, otherwise false.
         */
        bool SchemaAstWraper::validateArgument(const std::unique_ptr<InputValueDefinition> *argument,
                                               const facebook::graphql::ast::Value *value) {
            const Type &type = argument->get()->getType();
            const NonNullType &nonNullType = (const NonNullType &) type;
            const NamedType &nam = (NamedType &) nonNullType.getType();

            const char *valueType = nam.getName().getValue();

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

