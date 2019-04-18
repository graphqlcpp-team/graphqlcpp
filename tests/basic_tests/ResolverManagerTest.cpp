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
#include "GraphQlResolverTestData.cpp"
#include "../../../include/graphqlcpp/resolver/ResolverManager.h"

using namespace std;
using namespace GraphQlResolverTestData;
using namespace graphqlcpp::resolver;

#include <stdio.h>  /* defines FILENAME_MAX */


TEST(ResolverManager, IsOperationValid) {
    ResolverManager* rm = new ResolverManager();
    rm->registerResolver(GraphQlResolverTestData::ResolverOne);
}

