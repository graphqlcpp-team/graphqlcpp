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
	//TODO checken wegen destruktur
	//Evtl pointer gegen referenzen tauschen

	SchemaValidator sValidator;
	GraphqlCppApi api(&sValidator);
	return &api;
}
} /* namespace api */
} /* namespace graphqlcpp */


