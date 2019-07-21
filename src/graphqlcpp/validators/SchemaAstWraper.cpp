/*
 * SchemaAstWraper.cpp
 *
 *  Created on: 17.02.2019
 *      Author: julian2
 */

#include "../../../include/graphqlcpp/validators/SchemaAstWraper.h"
#include "../../../src/graphqlparser/c/GraphQLAstToJSON.h"
#include "../../../include/graphqlparser/Ast.h"
#include "../../../src/graphqlparser/c/GraphQLAst.h"
#include "../../../include/graphqlcpp/exceptions/NoSchemaSetException.h"
#include "../../../include/graphqlcpp/exceptions/ArgumentNotValidException.h"
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
         * This method validate if a node exists as the child of the root node.
         * If it exists as a child node, the arguments will be validated. It will be validated if all mandatory arguments
         * have been set.
         * It makes a difference whether the father node is the operation or not. That's because the types of the
         * nodes differ. Therefore the if condition.
         * First the field name is searched in the fields. If the name was found, the node name is extracted out of
         * the AST. This name can be searched in the other nodes, if a field with this name exists. If this is the
         * case the child field name exists as a child of the father node.
         * Afterwards the arguments will be validated.
         * @param fatherFieldName The name of the father field.
         * @param fieldQueryAst The field in the query AST.
         * @return True, if the node is valid.
         */
        bool SchemaAstWraper::validateNode(const char *fatherFieldName, const Field *fieldQueryAst) {
            const std::vector<std::unique_ptr<Definition>> &operationDefintion = getDocument()->getDefinitions();
            const char *fatherNodeName = nullptr;

            if (strcmp(fatherFieldName, "query") == 0 || strcmp(fatherFieldName, "mutation") == 0) {
                fatherNodeName = getFatherFieldNameIfFatherIsOperation(fatherFieldName);
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
            return fieldExistsAsChildOfFatherNodeWithRigthArguments(fieldQueryAst, operationDefintion, fatherNodeName);
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
            const auto *schemaDefinitionCasted =
                    (const GraphQLAstSchemaDefinition *) schemaDefinitioNotCasted;
            const auto *schemaDefinition =
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
         * This function will get the fathers node name from the field name.
         * This function should be called if the father node name is not an operation as query or mutation.
         * It is necessary to get the node name to find the father node in the AST. It is not possible to get the fathers
         * node with only the field name. The fathers node is necessary to get the child fields.
         * @param fatherFieldName The name of the father field as set in the query. This is exactly the name as in the query.
         * @param operationDefinitions The start point of the schema AST.
         * @return The father node name.
         */
        const char *SchemaAstWraper::getFatherNodeNameIfFatherIsNotOperation(const char *fatherFieldName,
                                                                             const std::vector<std::unique_ptr<facebook::graphql::ast::Definition>> &operationDefinitions) {
            const char *fatherNodeName = nullptr;
            //begin with 1 because the first element is the operation and is treated separate.
            for (auto operationDefinition = operationDefinitions.begin() + 1;
                 operationDefinition != operationDefinitions.end(); ++operationDefinition) {
                const auto *graphQLAstObjectTypeDefinition =
                        (const GraphQLAstObjectTypeDefinition *) operationDefinition->get();
                const auto *objectTypeDefinition =
                        (const ObjectTypeDefinition *) graphQLAstObjectTypeDefinition;
                const vector<unique_ptr<FieldDefinition>> &fields = objectTypeDefinition->getFields();

                for (const auto &field : fields) {
                    const char *fieldName = field->getName().getValue();
                    if (strcmp(fatherFieldName, fieldName) == 0) {
                        const Type *type = &field->getType();
                        const Type * listType = &((ListType*) type)->getType();
                        fatherNodeName= ((NamedType*)listType)->getName().getValue();
                        if(fatherNodeName == nullptr )
                        {
                            const NamedType *namedType = (NamedType *) type;
                            fatherNodeName = namedType->getName().getValue();
                        }
                        break;
                    }
                }
                if (fatherNodeName != nullptr) {
                    break;
                }
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
        const char *SchemaAstWraper::getFatherFieldNameIfFatherIsOperation(const char *fatherFieldName) {

            const char *fatherNodeName = nullptr;
            const SchemaDefinition *schemaDefinition = getSchemaDefinition();
            const vector<unique_ptr<OperationTypeDefinition>> &operationTypes = schemaDefinition->getOperationTypes();

            for (const auto &operationType : operationTypes) {
                const char *operationTyp = operationType->getOperation();
                if (strcmp(fatherFieldName, operationTyp) == 0) {
                    fatherNodeName = operationType->getType().getName().getValue();
                    break;
                }
            }
            return fatherNodeName;
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
        bool SchemaAstWraper::validateArgument(const char *valueType,
                                               const facebook::graphql::ast::Value *value) {

            if (strcmp(valueType, "ID") == 0 || strcmp(valueType, "String") == 0 || strcmp(valueType, "string") == 0) {
                try {
                    const StringValue *castedValue = (StringValue *) value;
                    const char *valueOfArgument = castedValue->getValue();
                }
                catch (...) {
                    return false;
                }

            } else if (strcmp(valueType, "int") == 0 || strcmp(valueType, "Int") == 0) {
                try {
                    const IntValue *intValue = (IntValue *) value;
                    const char *argumentsValue = intValue->getValue();
                    for (auto i = 0; argumentsValue[i] != '\0'; i++) {
                        if (argumentsValue[i] < '0' || argumentsValue[i] > '9')
                            return false;
                    }
                }
                catch (...) {
                    return false;
                }
            } else if (strcmp(valueType, "Float") == 0 || strcmp(valueType, "float") == 0) {
                try {
                    const FloatValue *floatValue = (FloatValue *) value;
                    const char *argumentsValue = floatValue->getValue();
                    bool pointWasThere = false;
                    for (auto i = 0; argumentsValue[i] != '\0'; i++) {
                        if (argumentsValue[i] == '.' && !pointWasThere) {
                            pointWasThere = true;
                            continue;
                        }
                        if (argumentsValue[i] < '0' || argumentsValue[i] > '9' ||
                            (argumentsValue[i] == '.' && pointWasThere))
                            return false;

                    }
                }
                catch (...) {
                    return false;
                }
            } else if (strcmp(valueType, "Boolean") == 0 || strcmp(valueType, "boolean") == 0) {
                try {
                    const StringValue *booleanValue = (StringValue *) value;
                    const char *argumentsValue = booleanValue->getValue();
                    return ((int *) &argumentsValue[0]) == (int *) 0x1 || ((int *) &argumentsValue[0]) == (int *) nullptr;
                }
                catch (...) {
                    return false;
                }
            }
            return true;
        }

        /**
         * It's conna be check if the field name of the child from the query exists as a child of the node.
         * Therefor there is an iteration through the child fields of the father node set in the query.
         * To get to the father node there is a iteration through the AST necessary, this is the first for-loop.
         * If we have the father node we can iterate through its fields (the second for-loop).
         * If a child node with the name of the child name set in the query is there, the arguments will be validated.
         * @param fieldQueryAst The field of the query AST.
         * @param operationDefinitions The start point of the schema AST.
         * @param fatherNodeName The father node name. This has to be extracted out of the AST.
         * @return True if the field exists as child of the father node and the argument(s) is valid, otherwise false.
         */
        bool SchemaAstWraper::fieldExistsAsChildOfFatherNodeWithRigthArguments(const Field *fieldQueryAst,
                                                                               const std::vector<std::unique_ptr<Definition>> &operationDefinitions,
                                                                               const char *fatherNodeName) {
            for (auto operationDefinition = operationDefinitions.begin() + 1;
                 operationDefinition != operationDefinitions.end(); ++operationDefinition) {
                const auto *graphQLAstObjectTypeDefinition =
                        (const GraphQLAstObjectTypeDefinition *) operationDefinition->get();
                const auto *objectTypeDefinition =
                        (const ObjectTypeDefinition *) graphQLAstObjectTypeDefinition;
                const char *typeDefinitionName = objectTypeDefinition->getName().getValue();

                if (strcmp(typeDefinitionName, fatherNodeName) == 0) {
                    //in this AST node the child node must be located

                    const vector<unique_ptr<FieldDefinition>> &fieldsSchemaAstChildNode = objectTypeDefinition->getFields();

                    for (const auto &fieldSchemaAstChildNode : fieldsSchemaAstChildNode) {
                        const char *fieldName = fieldSchemaAstChildNode->getName().getValue();
                        if (strcmp(fieldQueryAst->getName().getValue(), fieldName) == 0) {
                            //the child node exists as node of father node
                            return checkArguments(fieldQueryAst->getArguments(),
                                                  fieldSchemaAstChildNode->getArguments());
                        }
                    }
                }
            }
            return false;
        }

        /**
         * Iterate through each argument of the schema AST.
         * Check if the argument is a 'NonNullType', because the call hierarchy differs.
         * Foreach argument it will be checked if the query contains the argument. In case of a nullable type
         * the argument does not have to be set.
         * If the argument is in the query the arguments type will be validated.
         * @param argumentsQueryAst The arguments of the query AST.
         * @param argumentsSchemaAst The arguments of the schema AST.
         * @return true, if all mandatory arguments are set and the type is correct.
         */
        bool SchemaAstWraper::checkArguments(const std::vector<std::unique_ptr<Argument>> *argumentsQueryAst,
                                             const std::vector<std::unique_ptr<InputValueDefinition>> *argumentsSchemaAst) {
            if (argumentsQueryAst == nullptr & argumentsSchemaAst == nullptr)
                return true;
            for (const auto &argumentSchemaAst : *argumentsSchemaAst) {

                const Type &type = argumentSchemaAst->getType();

                const char *valueType;
                bool nullable = false;

                const char *nonNullTypeString = "NonNullType";
                auto typeOfType = typeid(type).name();
                if (strstr(typeOfType, nonNullTypeString) != nullptr) {
                    //Non null type
                    const auto &nonNullType = (const NonNullType &) type;
                    const NamedType &nam = (NamedType &) nonNullType.getType();
                    valueType = nam.getName().getValue();
                } else {
                    nullable = true;
                    const NamedType &nam = (NamedType &) type;
                    valueType = nam.getName().getValue();
                }

                const char *argumentName = argumentSchemaAst->getName().getValue();

                const facebook::graphql::ast::Value *valueAstArgument = checkIfQueryContainsArgument(argumentsQueryAst,
                                                                                                     argumentName);

                if (valueAstArgument == nullptr & nullable) {
                    //no value but nullable, so everything allright
                    continue;
                } else if (valueAstArgument == nullptr) {
                    //no value but not nullable, so an error
                    return false;
                }
                if (!validateArgument(valueType, valueAstArgument))
                    return false;
            }
            return true;
        }

        /**
         * This function checks if the query AST contains the argument name of the schema AST.
         * If there is no argument in the query AST a null pointer is returned.
         * If the query AST does containing it, the value of the argument will be returned.
         * @param argumentsQueryAst The arguments in the query AST.
         * @param argumentSchemaAstName The name of the argument of the schema AST which should be validate againt the query.
         * @return The value of the argument or nullptr if there is no argument in the query.
         */
        const Value *
        SchemaAstWraper::checkIfQueryContainsArgument(const std::vector<std::unique_ptr<Argument>> *argumentsQueryAst,
                                                      const char *argumentSchemaAstName) {

            //if there is no argument exit function with true
            if (argumentsQueryAst == nullptr) {
                return nullptr;
            }
            const std::vector<std::unique_ptr<Argument>> &argumentsQueryAstValue =
                    *argumentsQueryAst;

            for (const auto &argumentQueryAst : argumentsQueryAstValue) {
                const char *nameArgumentQueryAst = argumentQueryAst->getName().getValue();
                if (strcmp(nameArgumentQueryAst, argumentSchemaAstName) == 0) {
                    return &argumentQueryAst->getValue();
                }
            }
            return nullptr;
        }
    } /* namespace validators */
} /* namespace graphqlcpp */

