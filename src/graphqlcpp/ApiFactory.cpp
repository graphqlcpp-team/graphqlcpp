/*
 * ApiFactory.cpp
 *
 *  Created on: 10.02.2019
 *      Author: amelie
 */

#include "../../include/graphqlcpp/ApiFactory.h"
#include "../../include/graphqlcpp/GraphqlCppApi.h"

namespace graphqlcpp {
namespace api {
ApiFactory::ApiFactory() {
}

GraphqlCppApi* ApiFactory::createApi() {
	return new GraphqlCppApi();
}
} /* namespace api */
} /* namespace graphqlcpp */


