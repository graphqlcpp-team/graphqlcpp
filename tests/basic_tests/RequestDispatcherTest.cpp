//
// Created by julian on 18.04.19.
//
#include "../../include/graphqlcpp/dispatcher/RequestDispatcher.h"


#include "gtest/gtest.h"
#include "../../src/graphqlparser/GraphQLParser.h"


using namespace graphqlcpp::dispatcher;

TEST(RequestDispatcherTest, simpleTest) {
    auto resManager = new ResolverManager();
    auto dispatcher = new RequestDispatcher(resManager);

    const char *query = "query{user(id:1) {name: hallo}}";
    const char *error = nullptr;
    std::unique_ptr<Node> queryAst;
    queryAst = facebook::graphql::parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    Node *node = queryAst.get();
    graphqlcpp::RequestAstWrapper *wrapper = new graphqlcpp::RequestAstWrapper(node);

    string res;
    res = dispatcher->executeRequest(wrapper);


    delete resManager;
    delete dispatcher;
}