//
// Created by julian on 11.04.19.
//

#include "../../../include/graphqlcpp/resolver/ResolverManager.h"

graphqlcpp::resolver::ResolverManager::ResolverManager() {
    this->resolvers = new std::map<std::string, IGraphQlResolver*>();
}

graphqlcpp::resolver::ResolverManager::~ResolverManager() {
    delete this->resolvers;
    //TODO inhalt der map deleten. Oder funtioniert das automatisch?
}

void graphqlcpp::resolver::ResolverManager::registerResolver(graphqlcpp::resolver::IGraphQlResolver *resolver) {
    this->resolvers->insert(std::make_pair(resolver->getResolverName(),resolver));

}

graphqlcpp::api::IGraphQlDTO *
graphqlcpp::resolver::ResolverManager::executeResolver(std::string resolverName, const std::vector<ResolverArgument*> *args) {
    std::map<std::string, IGraphQlResolver *> &rmap = *(this->resolvers);
    IGraphQlResolver *resolver = rmap[resolverName];
    return resolver->execute(args);
}
