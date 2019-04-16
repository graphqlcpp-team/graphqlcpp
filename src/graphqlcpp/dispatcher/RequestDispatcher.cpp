//
// Created by julian on 13.04.19.
//

#include "../../../include/graphqlcpp/dispatcher/RequestDispatcher.h"


std::string
graphqlcpp::dispatcher::RequestDispatcher::executeRequest(RequestAstWrapper *requestAstWrapper) {
    auto operation = requestAstWrapper->extractOperation();
    if (operation == "query") {
        auto resolver = requestAstWrapper->extractResolver();
        auto data = this->resolverManager->executeResolver(resolver->getResolverName(), resolver->getArgs());
        auto serializer = new MySerializer(requestAstWrapper->extractSelectionSetForSerialisation());
        std::string json = data->serialize(serializer)->createJson()->getJson();
        delete serializer;
        return json;
    }
    return nullptr; //TODO use exception
}

graphqlcpp::dispatcher::RequestDispatcher::RequestDispatcher(graphqlcpp::resolver::ResolverManager *resolverManager,
                                                             graphqlcpp::validators::SchemaAstWraper *schemaAstWraper) {
    this->schemaAstWraper = schemaAstWraper;
    this->resolverManager = resolverManager;

}

