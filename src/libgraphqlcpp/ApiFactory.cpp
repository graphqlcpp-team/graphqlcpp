/*
 * ApiFactory.cpp
 *
 *  Created on: 10.02.2019
 *      Author: amelie
 */

#include "ApiFactory.h"
#include "GraphqlCppApi.h"

namespace graphqlcpp {
namespace api {
ApiFactory::ApiFactory() {
}

GraphqlCppApi* ApiFactory::createApi() {
	return new GraphqlCppApi();
}
} /* namespace api */
} /* namespace graphqlcpp */


