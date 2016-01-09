#include "database_private.h"
#include "exception.h"

namespace arango {

database::impl::impl(const std::string &host, const std::string &database,
										 const std::string &username, const std::string &password)
	: host(host), database(database), authentication(username, password)
{

}

std::string database::impl::getUrl(const std::string &postfix) {
	return host + "/_db/" + database + "/_api/" + postfix;
}

void database::impl::validateResponse(const cpr::Response &response)
{
	switch(response.status_code) {
		case 0: // Connection error
			throw connection_exception(response.error.message);
		case 401: // Unauthorized
			throw unauthorized_exception();
	}
}

}
