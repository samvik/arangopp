#ifndef ARANGO_DATABASE_PRIVATE_H
#define ARANGO_DATABASE_PRIVATE_H

#include "database.h"
#include <cpr/cpr.h>

namespace arango {
struct database::impl {
		impl(const std::string &host, const std::string &database,
				 const std::string &username, const std::string &password);

		std::string host;
		std::string database;

		cpr::Authentication authentication;

		std::string getUrl(const std::string &postfix);
		void validateResponse(const cpr::Response &response);
};
}

#endif // DATABASE_PRIVATE_H
