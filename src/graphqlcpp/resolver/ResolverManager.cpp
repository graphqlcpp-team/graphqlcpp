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
