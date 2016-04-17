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

json database::impl::validateResponse(const cpr::Response &response)
{
	if(response.error.code != cpr::ErrorCode::OK) {
		throw connection_exception(response.error.message);
	}

	auto obj = json::parse(response.text);

	if(obj["error"].get<bool>()) {
		switch(obj["code"].get<int>()) {
			case 400:
				throw bad_request_exception(obj["errorMessage"].get<std::string>());
			case 401: // Unauthorized
				throw unauthorized_exception(obj["errorMessage"].get<std::string>());
			case 404:
				throw not_found_exception(obj["errorMessage"].get<std::string>());
			case 409:
				throw conflict_exception(obj["errorMessage"].get<std::string>());
			default:
				throw http_exception(obj["errorMessage"].get<std::string>());
		}
	}

	return obj;
}

}
