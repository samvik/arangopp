#ifndef ARANGO_DATABASE_PRIVATE_H
#define ARANGO_DATABASE_PRIVATE_H

#include "database.h"
#include <cpr/cpr.h>

namespace arango {
struct database::impl {
		std::string host;
		std::string database;
		std::string username;
		std::string password;

		std::string getUrl(const std::string &postfix);
};
}

#endif // DATABASE_PRIVATE_H
