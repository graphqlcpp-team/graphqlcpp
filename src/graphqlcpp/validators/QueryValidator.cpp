/*
 * QueryValidator.cpp
 *
 *  Created on: 17.02.2019
 *      Author: amelie
 */

#include "QueryValidator.h"
#include "../../libgraphqlparser/c/GraphQLAst.h"
#include "../../libgraphqlparser/Ast.h"
#include "../exceptions/WrongOperationException.h"
#include <vector>
#include <memory>

namespace graphqlcpp {
namespace validators {

using namespace graphqlcpp::exceptions;

QueryValidator::QueryValidator(SchemaAstWraper* schemaWrapper) {
	this->schemaWrapper = schemaWrapper;

}
bool QueryValidator::isQueryValid(Node* rootNodeQuery) {
	const char* operation = getOperation(rootNodeQuery);
	const SelectionSet* selectionSet = getSelectionSet(rootNodeQuery);
	char nullChar = '\0';
	const char* firstElement = &nullChar;
	if (!iterateThroughSelectionSetsAndValidate(selectionSet, firstElement)) {
		//throw (); TODO
		return false;
	}
	if (operation != "query") {
		throw WrongOperationException();
		return false;
	}

	return false;
}

using namespace std;
using namespace facebook::graphql;
using namespace facebook::graphql::ast;

bool QueryValidator::iterateThroughSelectionSetsAndValidate(
		const SelectionSet* selectionSet, const char* oldFieldName) {
	if (selectionSet != 0x0) {

		const std::vector<std::unique_ptr<Selection>>& selectionSetArray =
				selectionSet->getSelections();
		int index = 0;
		for (auto i = selectionSetArray.begin(); i != selectionSetArray.end();
				++i) {
			const GraphQLAstField* graphQlField =
					(GraphQLAstField*) selectionSetArray[index].get();
			const Field* field = (const Field *) graphQlField;
			const Name* namePointer = &field->getName();
			const char* name = namePointer->getValue();
			if (!this->schemaWrapper->nodeExsitstsAsChildOf(name,
					oldFieldName)) {
				return false;
			}
			//const vector<unique_ptr<Argument, default_delete<Argument>>,
			//		allocator<unique_ptr<Argument, default_delete<Argument>>>> * argumentPointer =
			//		field->getArguments();
			if(!iterateThroughArgumentsOfOneFiledAndValidate(field)) {
				return false;
			}
			const SelectionSet* selectionSetOfField = field->getSelectionSet();
			if (!iterateThroughSelectionSetsAndValidate(selectionSetOfField,
					name)) {
				return false;
			}
			index++;
		}
	}
	return true;
}

bool QueryValidator::iterateThroughArgumentsOfOneFiledAndValidate(
		const Field* field) {
	const std::vector<std::unique_ptr<Argument>>* argumentPointer =
			field->getArguments();
	const std::vector<std::unique_ptr<Argument>>& argumentArray =
			*argumentPointer;
	int index = 0;
	for (auto j = argumentArray.begin(); j != argumentArray.end(); ++j) {
		std::unique_ptr<Argument, default_delete<Argument>>::pointer argumentPointerOneField =
				argumentArray[index].get(); //->size();
		const GraphQLAstArgument* graphQLAstArgument =
				(GraphQLAstArgument*) argumentPointerOneField;
		const Argument* argument = (const Argument*) graphQLAstArgument;
		if (argument != 0x0) {
			const Name* nameA = &argument->getName();
			const char* nameAr = nameA->getValue();
			const Value& valueA = argument->getValue();
			const Value* pointerA = &valueA;

			//pointerA.getValue();
			cout << "Name Argument: " << nameAr << endl;
		}
		index++;
	}
	return true;
}

const char* QueryValidator::getOperation(Node* rootNodeQuery) {
	const OperationDefinition *realNodeOpDef = getOperationDefinition(
			rootNodeQuery);
	const char* operation = realNodeOpDef->getOperation();
	return operation;
}

const SelectionSet* QueryValidator::getSelectionSet(Node* rootNodeQuery) {
	const OperationDefinition *realNodeOpDef = getOperationDefinition(
			rootNodeQuery);
	const GraphQLAstSelectionSet * graphQlSelectionSet =
			(const struct GraphQLAstSelectionSet *) &realNodeOpDef->getSelectionSet();
	const SelectionSet* selectionSet =
			(const SelectionSet *) graphQlSelectionSet;
	return selectionSet;
}

const OperationDefinition* QueryValidator::getOperationDefinition(
		Node* rootNodeQuery) {
	const GraphQLAstDocument* graphQlAstDocument =
			(const struct GraphQLAstDocument *) rootNodeQuery;
	const Document *realNode = (const Document *) graphQlAstDocument;
	const std::vector<std::unique_ptr<Definition>>& x =
			realNode->getDefinitions();
	std::unique_ptr<Definition, default_delete<Definition>>::pointer operationDefinitioNotCasted =
			x[0].get();
	const GraphQLAstOperationDefinition * operationDefinitionCasted =
			(const GraphQLAstOperationDefinition *) operationDefinitioNotCasted;
	const OperationDefinition *realNodeOpDef =
			(const OperationDefinition *) operationDefinitionCasted;
	return realNodeOpDef;
}

/*void QueryValidator::iterateThroughAST(Node* rootNodeQuery) {
 const GraphQLAstSelectionSet* selectionSet = getSelectionSet(rootNodeQuery);
 //do we need to operate through every operationDefinition?
 //Need to operate through every field

 const std::vector<std::unique_ptr<Selection>>& selec =
 realNode->getSelections();

 const GraphQLAstField* graphQlAstFiel = (GraphQLAstField*) selec[0].get();
 const Field* realNodeField = (const Field *) graphQlAstFiel;
 const Name* name = &realNodeField->getName();

 const char* nameOfField = name->getValue();

 const SelectionSet* selectionSetn = realNodeField->getSelectionSet();
 const std::vector<std::unique_ptr<Selection>>& selecN =
 selectionSetn->getSelections();
 int index = 0;
 for (auto i = selecN.begin(); i != selecN.end(); ++i) {
 const GraphQLAstField* graphQlAstFielN =
 (GraphQLAstField*) selecN[index].get();
 const Field* realNodeFieldN = (const Field *) graphQlAstFielN;
 const auto nameNN = &realNodeFieldN->getName();
 auto nameNNN = nameNN->getValue();
 index++;
 }

 auto sizeA = sizeof(&selecN);
 auto sizeB = sizeof(selecN);
 //auto sizeC = sizeof(*selecN);
 size_t size = sizeof(&selecN) / sizeof(selecN);
 //const __gnu_cxx::__alloc_traits<allocator<unique_ptr<Selection,default_delete<Selection>>>>::value_type test = selecN[0];
 for (unsigned int a = 0; a < size; a = a + 1) {
 }

 //const auto name =   (const struct GraphQLAstName *)&realNodeField->getName();
 //const Selection* field = (Selection*)selec[0];
 //const auto selection = realNode->getSelections();

 }*/

} /* namespace api */
} /* namespace graphqlcpp */
