//
// Created by julian on 13.04.19.
//

#include "../../../include/graphqlcpp/dispatcher/RequestDispatcher.h"


std::string
graphqlcpp::dispatcher::RequestDispatcher::executeRequest(RequestAstWrapper *requestAstWrapper) {
    std::string operation = requestAstWrapper->extractOperation();
    if (operation == "query") {
        ResolverInfo * resolver;
        resolver = requestAstWrapper->extractResolver();
        IGraphQlDTO * data;
        data = this->resolverManager->executeResolver(resolver->getResolverName(), resolver->getArgs());
        MySerializer * serializer;
        serializer = new MySerializer(requestAstWrapper->extractSelectionSetForSerialisation());
        std::string json = data->serialize(serializer)->createJson()->getJson();
        delete serializer;
        return json;
    }
    return nullptr; //TODO use exception
}

graphqlcpp::dispatcher::RequestDispatcher::RequestDispatcher(graphqlcpp::resolver::ResolverManager *resolverManager) {
    this->resolverManager = resolverManager;

}

