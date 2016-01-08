#include "database_private.h"

namespace arango {

std::string database::impl::getUrl(const std::string &postfix) {
	return host + "/_db/" + database + "/_api/" + postfix;
}

}
