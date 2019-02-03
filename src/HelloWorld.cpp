//============================================================================
// Name        : HelloWorld.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "libgraphqlparser/GraphQLParser.h"
#include "libgraphqlparser/Ast.h"
#include "libgraphqlparser/AstNode.h"
#include <memory>

using namespace std;
using namespace facebook;
using namespace graphql;
using namespace ast;


void testGraphQlParser();

/**
int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	//return 0;
	testGraphQlParser();
	return 0;
}
*/

void testGraphQlParser(){
	const char* x = "{me{name}}";
	const char** err = NULL;
	unique_ptr<ast::Node> res = facebook::graphql::parseString(x, err);
	//cout << res << endl;
}
