/*
 * SchemaAstWrapperTest.cpp
 *
 *  Created on: 20.02.2019
 *      Author: Peter
 */


#include"gtest/gtest.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "../../include/graphqlparser/Ast.h"
#include "../../src/graphqlparser/GraphQLParser.h"
#include "../../src/graphqlparser/c/GraphQLAstToJSON.h"
#include "../../include/graphqlcpp/RequestAstWrapper.h"
#include "../../include/graphqlcpp/exceptions/WrongOperationException.h"
#include "../../include/graphqlcpp/exceptions/InvalidRequestException.h"


using namespace std;
using namespace facebook::graphql;
using namespace facebook::graphql::ast;
using namespace graphqlcpp;
using namespace graphqlcpp::exceptions;

#include <stdio.h>  /* defines FILENAME_MAX */


TEST(RequestAstWrapperTest, IsOperationValid) {
    const char *error = nullptr;
    const char *query = "query{user(id:1) {name: hallo}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    Node *node = queryAst.get();
    RequestAstWrapper *raw = new RequestAstWrapper(node);
    std::string operation = raw->extractOperation();
    ASSERT_TRUE(operation == "query");
}

TEST(RequestAstWrapperTest, IsSelectionSetNotNull) {
    const char *error = nullptr;
    const char *query = "query{user(id:1){name age}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    Node *node = queryAst.get();
    RequestAstWrapper *raw = new RequestAstWrapper(node);
    const SelectionSet *operation = raw->extractSelectionSetForSerialisation();
    ASSERT_FALSE(operation == nullptr);
}

TEST(RequestAstWrapperTest, IsResolverNameValid) {
    const char *error = nullptr;
    const char *query = "query{user(id:1){name age}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    Node *node = queryAst.get();
    RequestAstWrapper *raw = new RequestAstWrapper(node);
    ResolverInfo resolverInfo = raw->extractResolver();
    std::string name = resolverInfo.getResolverName();
    ASSERT_TRUE(name == "user");
}

TEST(RequestAstWrapperTest, AreResolverArgumentsValid) {
    const char *error = nullptr;
    const char *query = "query{user(id:1){name age}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    Node *node = queryAst.get();
    RequestAstWrapper *raw = new RequestAstWrapper(node);
    ResolverInfo resolverInfo = raw->extractResolver();
    vector<ResolverArgument *> * resolverArguments = resolverInfo.getArgs();
    ASSERT_TRUE(resolverArguments->at(0)->getArgName() == "id");
    ASSERT_TRUE(resolverArguments->at(0)->getArgValue() == "1");
}


TEST(RequestAstWrapperTest, AreResolverArgumentsValidWithNoValue) {
    const char *error = nullptr;
    const char *query = "query{user {name age}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    Node *node = queryAst.get();
    RequestAstWrapper *raw = new RequestAstWrapper(node);
    ResolverInfo resolverInfo  = raw->extractResolver();
    vector<ResolverArgument *> *resolverArguments = resolverInfo.getArgs();
    ASSERT_EQ(resolverArguments, nullptr);
}

TEST(RequestAstWrapperTest, AreResolverArgumentsValidTrueValue) {
    const char *error = nullptr;
    const char *query = "query{user(id:true){name age}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    Node *node = queryAst.get();
    RequestAstWrapper *raw = new RequestAstWrapper(node);
    ResolverInfo resolverInfo = raw->extractResolver();
    vector<ResolverArgument *> * resolverArguments = resolverInfo.getArgs();
    ASSERT_TRUE(resolverArguments->at(0)->getArgName() == "id");
    ASSERT_TRUE(resolverArguments->at(0)->getArgValue() == "true");
}

TEST(RequestAstWrapperTest, AreResolverArgumentsValidFalseValue) {
    const char *error = nullptr;
    const char *query = "query{user(id:false){name age}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    Node *node = queryAst.get();
    RequestAstWrapper *raw = new RequestAstWrapper(node);
    ResolverInfo resolverInfo= raw->extractResolver();
    vector<ResolverArgument *> * resolverArguments = resolverInfo.getArgs();
    ASSERT_TRUE(resolverArguments->at(0)->getArgName() == "id");
    ASSERT_TRUE(resolverArguments->at(0)->getArgValue() == "false");
}

TEST(RequestAstWrapperTest, AreResolverArgumentsValidTwoValues) {
    const char *error = nullptr;
    const char *query = "query{user(id:false age:22){name age}}";
    std::unique_ptr<Node> queryAst;
    queryAst = parseString(query, &error);
    ASSERT_TRUE(query);
    ASSERT_FALSE(error);

    Node *node = queryAst.get();
    RequestAstWrapper *raw = new RequestAstWrapper(node);
    ResolverInfo resolverInfo = raw->extractResolver();
    vector<ResolverArgument *> * resolverArguments = resolverInfo.getArgs();
    ASSERT_TRUE(resolverArguments->at(0)->getArgName() == "id");
    ASSERT_TRUE(resolverArguments->at(0)->getArgValue() == "false");
    ASSERT_TRUE(resolverArguments->at(1)->getArgName() == "age");
    ASSERT_TRUE(resolverArguments->at(1)->getArgValue() == "22");
}