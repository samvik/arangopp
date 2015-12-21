#ifndef ARANGO_QUERY_CURSOR_PRIVATE_H
#define ARANGO_QUERY_CURSOR_PRIVATE_H

#include "query_cursor.h"

#include <cpr/cpr.h>
#include <functional>

namespace arango {

struct query_cursor::impl {

	typedef std::function<json()> get_more_func;

	impl(json result, get_more_func get_more_f)
		: get_more_f(get_more_f), result(result)
	{
	}

	bool get_more() {
		result = get_more_f();
		return result["code"].get<unsigned>() == 201;
	}

	get_more_func get_more_f;
	json result;
};

}


#endif // ARANGO_QUERY_CURSOR_PRIVATE_H
