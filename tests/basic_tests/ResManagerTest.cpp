#include"gtest/gtest.h"
#include "../../include/graphqlparser/Ast.h"
#include "../../src/graphqlparser/GraphQLParser.h"
#include "../../src/graphqlparser/c/GraphQLAstToJSON.h"
#include "../../include/graphqlcpp/resolver/ResolverManager.h"
#include "../../include/graphqlcpp/resolver/IGraphQlResolver.h"
#include "TestData.cpp"

using namespace facebook::graphql;
using namespace facebook::graphql::ast;
using namespace graphqlcpp::resolver;

class MyResolver : public IGraphQlResolver
{
    char *getResolverName() override {
        return "allFilms";
    }

    IGraphQlDTO *execute(ResolverArgument *resolverArgs) override {
        auto cu = demo::TestDataGenerator::createCustomer();
        return cu;
    }

};

TEST(ResManagerTest, simpleTest){
    ResolverManager* rm = new ResolverManager();
    IGraphQlResolver* res = new MyResolver();
    rm->registerResolver(res);
}

/*
TEST(LibTests, SchemaToAst) {
    char buff[FILENAME_MAX];
    GetCurrentDir(buff, FILENAME_MAX);
    std::string current_working_dir(buff);
    std::cout << current_working_dir;
	FILE *pFile;
 	pFile = fopen("schema-test-user.graphql", "r");
	ASSERT_TRUE(pFile != NULL);
	const char *error = nullptr;
	std::unique_ptr<Node> ast;
	ast = parseFileWithExperimentalSchemaSupport(pFile, &error);

	ASSERT_TRUE(ast);
	ASSERT_FALSE(error);
	fclose(pFile);

	const char *json = graphql_ast_to_json((const struct GraphQLAstNode *)ast.get());
	ofstream outputFile;
	outputFile.open("schema-test-user.json");
	outputFile << json;
	outputFile.close();

	const char* schema = "schema {query: Query} type Query { user(id: ID!): User} type User { id: ID! name: string!	age: Int}";
	std::unique_ptr<Node> ast2;
	ast2 = parseStringWithExperimentalSchemaSupport(schema, &error);
	ASSERT_TRUE(ast2);
	ASSERT_FALSE(error);
	const char *jsonSchemaString = graphql_ast_to_json((const struct GraphQLAstNode *)ast.get());
	ofstream outputFileString;
	outputFileString.open("schema-test-user_string.json");
	outputFileString << jsonSchemaString;
	outputFileString.close();

	const char * query = "{user(id:1) {age, name}}";
	std::unique_ptr<Node> queryAst;
	queryAst = parseString(query, &error);
	ASSERT_TRUE(query);
	ASSERT_FALSE(error);
	const char *jsonQueryString = graphql_ast_to_json((const struct GraphQLAstNode *)queryAst.get());
	ofstream outputFileQuery;
	outputFileQuery.open("query-test-user.json");
	outputFileQuery << jsonQueryString;
	outputFileQuery.close();

	free((void *)json);
	free((void *)jsonSchemaString);
	free((void *)jsonQueryString);
}
*/