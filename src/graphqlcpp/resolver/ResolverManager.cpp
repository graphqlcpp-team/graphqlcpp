//
// Created by julian on 11.04.19.
//

#include "../../../include/graphqlcpp/resolver/ResolverManager.h"

graphqlcpp::resolver::ResolverManager::ResolverManager() {
    this->resolvers = new std::map<char*, IGraphQlResolver*>();
}

graphqlcpp::resolver::ResolverManager::~ResolverManager() {
    delete this->resolvers;

}

void graphqlcpp::resolver::ResolverManager::registerResolver(graphqlcpp::resolver::IGraphQlResolver *resolver) {
    this->resolvers->insert(std::make_pair(resolver->getResolverName(),resolver));

}

graphqlcpp::api::IGraphQlDTO *
graphqlcpp::resolver::ResolverManager::executeResolver(char *resolverName, const std::vector<ResolverArgument> &args) {
    std::map<char *, IGraphQlResolver *> &rmap = *(this->resolvers);
    IGraphQlResolver *resolver = rmap[resolverName];
    return resolver->execute(args);
}
