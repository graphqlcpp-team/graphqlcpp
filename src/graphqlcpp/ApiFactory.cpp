/*
 * ApiFactory.cpp
 *
 *  Created on: 10.02.2019
 *      Author: amelie
 */

#include "ApiFactory.h"
#include "api/GraphqlCppApi.h"

namespace graphqlcpp {
namespace api {
ApiFactory::ApiFactory() {
}

GraphqlCppApi* ApiFactory::createApi() {
	//TODO checken wegen destruktur
	//Evtl pointer gegen referenzen tauschen

	SchemaValidator* sValidator = new SchemaValidator();
	QueryValidator* queryValidator = new QueryValidator();
	GraphqlCppApi* api = new GraphqlCppApi(sValidator, queryValidator);
	return api;
}
} /* namespace api */
} /* namespace graphqlcpp */


