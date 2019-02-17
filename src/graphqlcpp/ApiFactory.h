/*
 * ApiFactory.h
 *
 *  Created on: 10.02.2019
 *      Author: amelie
 */

#ifndef APIFACTORY_H_
#define APIFACTORY_H_

#include "api/GraphqlCppApi.h"

namespace graphqlcpp {
namespace api {

class ApiFactory {
	private:
		ApiFactory();
	public:
		static GraphqlCppApi* createApi();
};

} /* namespace api */
} /* namespace graphqlcpp */

#endif /* APIFACTORY_H_ */
