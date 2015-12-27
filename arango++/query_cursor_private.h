#ifndef ARANGO_QUERY_CURSOR_PRIVATE_H
#define ARANGO_QUERY_CURSOR_PRIVATE_H

#include "query_cursor.h"

#include <cpr/cpr.h>
#include <functional>

namespace arango {

struct query_cursor::impl {

		typedef std::function<json()> create_cursor_func;
		typedef std::function<json(const std::string&)> read_next_func;
		typedef std::function<bool(const std::string&)> delete_cursor_func;

		impl(create_cursor_func create_cursor_f, read_next_func get_more_f, delete_cursor_func delete_cursor_f)
			: create_cursor(create_cursor_f), read_next(get_more_f), delete_cursor(delete_cursor_f)
		{
			result = create_cursor_f();
		}

		bool get_more() {
			const std::string &id = result["id"].get<std::string>();
			result = read_next(id);
			return result["code"].get<unsigned>() == 201;
		}

		create_cursor_func create_cursor;
		read_next_func read_next;
		delete_cursor_func delete_cursor;

		json result;
};

}


#endif // ARANGO_QUERY_CURSOR_PRIVATE_H
