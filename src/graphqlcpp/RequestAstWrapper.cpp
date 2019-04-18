//
// Created by amelie on 16.04.19.
//

#include "../../include/graphqlcpp/RequestAstWrapper.h"

#include "../../../include/graphqlcpp/validators/QueryValidator.h"
#include "../../graphqlparser/c/GraphQLAst.h"
#include "../../../include/graphqlparser/Ast.h"
#include "../../../include/graphqlcpp/exceptions/InvalidQueryException.h"
#include "../../../include/graphqlcpp/exceptions/WrongOperationException.h"

namespace graphqlcpp {
    using namespace graphqlcpp::exceptions;

    using namespace facebook::graphql;
    using namespace facebook::graphql::ast;

    graphqlcpp::RequestAstWrapper::RequestAstWrapper(facebook::graphql::ast::Node *queryRootNode) {
        this->queryRootNode = queryRootNode;
    }

    graphqlcpp::ResolverInfo *graphqlcpp::RequestAstWrapper::extractResolver() {
        return nullptr;
    }

    /**
     * This method gets the operation of the query.
     * @param rootNodeQuery The root node of the query AST.
     * @return The operation.
     */
    const char *graphqlcpp::RequestAstWrapper::getOperation(facebook::graphql::ast::Node *rootNodeQuery) {
        const GraphQLAstDocument *graphQlAstDocument =
                (const struct GraphQLAstDocument *) rootNodeQuery;
        const Document *realNode = (const Document *) graphQlAstDocument;
        const std::vector<std::unique_ptr<Definition>> &definition =
                realNode->getDefinitions();
        std::unique_ptr<Definition, default_delete<Definition>>::pointer operationDefinitioNotCasted =
                definition[0].get();
        const GraphQLAstOperationDefinition *operationDefinitionCasted =
                (const GraphQLAstOperationDefinition *) operationDefinitioNotCasted;
        const OperationDefinition *operationDefinition =
                (const OperationDefinition *) operationDefinitionCasted;

        const char *operation = operationDefinition->getOperation();
        return operation;
    }

    std::string graphqlcpp::RequestAstWrapper::extractOperation() {
        return std::string(getOperation(queryRootNode));
    }

    facebook::graphql::ast::SelectionSet *graphqlcpp::RequestAstWrapper::extractSelectionSetForSerialisation() {
        return nullptr;
    }

}
