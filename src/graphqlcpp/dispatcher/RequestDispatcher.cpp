//
// Created by julian on 13.04.19.
//

#include "../../../include/graphqlcpp/dispatcher/RequestDispatcher.h"
#include "../../../include/graphqlcpp/resolver/ResolverInfo.h"
#include "../../../include/graphqlcpp/IGraphQlDTO.h"
#include "../../../include/graphqlcpp/utils/MySerializerRoot.h"
#include "../../../include/graphqlcpp/utils/MyWriter.h"
#include "../../../include/graphqlcpp/RequestAstWrapper.h"
#include "../../../include/graphqlcpp/exceptions/WrongOperationException.h"
#include <string>



std::string
graphqlcpp::dispatcher::RequestDispatcher::executeRequest(graphqlcpp::RequestAstWrapper *requestAstWrapper) {
    std::string operation = requestAstWrapper->extractOperation();
    if (operation == "query") {
        ResolverInfo resolver = requestAstWrapper->extractResolver();
        IGraphQlDTO* data = this->resolverManager->executeResolver(resolver.getResolverName(), resolver.getArgs());
        MySerializer * serializer = new MySerializerRoot(requestAstWrapper->extractSelectionSetForSerialisation());
        std::string json = data->serialize(serializer)->createJson().getJson();
        delete serializer;
        return json;
    }
    //expand here for more operations
    throw exceptions::WrongOperationException();
}

graphqlcpp::dispatcher::RequestDispatcher::RequestDispatcher(graphqlcpp::resolver::ResolverManager *resolverManager) {
    this->resolverManager = resolverManager;

}

