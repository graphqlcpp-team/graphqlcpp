//
// Created by julian on 18.04.19.
//
#include "../../include/graphqlcpp/dispatcher/RequestDispatcher.h"


#include "gtest/gtest.h"
#include "../../src/graphqlparser/GraphQLParser.h"
#include "GraphQlResolverTestData.cpp"
#include <iostream>

using namespace graphqlcpp::dispatcher;

TEST(RequestDispatcherTest, simpleTest) {
    auto resManager = new ResolverManager();

    resManager->registerResolver(new GraphQlResolverTestData::ResolverOne());

    auto dispatcher = new RequestDispatcher(resManager);

    const char *query = "query{ user { name }}";
    const char *error = nullptr;
    std::unique_ptr<Node> queryAst;
    queryAst = facebook::graphql::parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    Node *node = queryAst.get();
    graphqlcpp::RequestAstWrapper *wrapper = new graphqlcpp::RequestAstWrapper(node);

    string res;
    res = dispatcher->executeRequest(wrapper);
    std::cout << "Result is: " << res;

    delete resManager;
    delete dispatcher;
}