/*
 * SchemaAstWraper.h
 *
 *  Created on: 17.02.2019
 *      Author: julian2
 */

#ifndef SCHEMAASTWRAPER_H_
#define SCHEMAASTWRAPER_H_

#include <memory>
#include <vector>
#include "../../graphqlparser/Ast.h"

namespace graphqlcpp {
namespace validators {

using namespace facebook::graphql::ast;

class SchemaAstWraper {
private:
	Node* schema = nullptr;


public:
    /**
     * Constructor of the class schemaAstNode.          *
     * @param schemaAstRootNode The root node of the schema AST.
     */
    explicit SchemaAstWraper(Node* schemaAstRootNode);
    /**
     * This method convert the schema AST to the json format.
     * @return The schema as a JSON string.
     * @throw NoSchemaSetException if no schema was set.
     */
	const char* printSchemaAsJson();
    /**
     * This method checks if the operation is a operation which is set in the schema.
     * Iterates through every operation set in the schema AST. If the transfered operation does not exists
     * in the operation types it is not a valid operation.
     * @param operation The oepration which schould be validate against the schema AST.
     * @return True, if the operation is valid. Otherwise false.
     */
	bool isOperationValid(const char* operation);
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
	bool validateNode(const char* fatherFieldName, const Field * fieldQueryAst);
private:
    /**
     * This method gets the document. This is the root element of the schema AST.
     * @return The document.
     * @throw NoSchemaSetException if the schema is not set.
     */
    const Document* getDocument();
    /**
     * This method gets the schema definition of the schema.
     * The schema definition is necessary to get the operation set in the schema.
     * The schema AST is an array and the first element is a schema definition.
     * @return The schema definition of the schema AST.
     */
    const SchemaDefinition* getSchemaDefinition();
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
	bool validateArgument(const char *valueType, const Value* value);
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
    const char *getFatherFieldNameIfFatherIsOperation(const char *fatherFieldName);
    /**
     * This function will get the fathers node name from the field name.
     * This function should be called if the father node name is not an operation as query or mutation.
     * It is necessary to get the node name to find the father node in the AST. It is not possible to get the fathers
     * node with only the field name. The fathers node is necessary to get the child fields.
     * @param fatherFieldName The name of the father field as set in the query. This is exactly the name as in the query.
     * @param operationDefinitions The start point of the schema AST.
     * @return The father node name.
     */
    const char *getFatherNodeNameIfFatherIsNotOperation(const char *fatherFieldName,
            const std::vector<std::unique_ptr<Definition>> & operationDefinitions);
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
	bool fieldExistsAsChildOfFatherNodeWithRigthArguments(const Field *fieldQueryAst,
														  const std::vector<std::unique_ptr<Definition>> &operationDefinition,
														  const char *fatherNodeName);
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
	bool checkArguments(const std::vector<std::unique_ptr<Argument>> *argumentsQueryAst,
						const std::vector<std::unique_ptr<InputValueDefinition>> *argumentsSchemaAst);
    /**
     * This function checks if the query AST contains the argument name of the schema AST.
     * If there is no argument in the query AST a null pointer is returned.
     * If the query AST does containing it, the value of the argument will be returned.
     * @param argumentsQueryAst The arguments in the query AST.
     * @param argumentSchemaAstName The name of the argument of the schema AST which should be validate againt the query.
     * @return The value of the argument or nullptr if there is no argument in the query.
     */
	const Value * checkIfQueryContainsArgument(const std::vector<std::unique_ptr<Argument>> *argumentsQueryAst,
											 const char *argumentSchemaAstName);
};

} /* namespace validators */
} /* namespace graphqlcpp */

#endif /* SCHEMAASTWRAPER_H_ */
