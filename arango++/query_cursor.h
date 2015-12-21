#ifndef ARANGO_QUERY_CURSOR_H
#define ARANGO_QUERY_CURSOR_H

#include <memory>
#include "json.h"

namespace arango {

class query_cursor
{
	public:
		bool is_valid() const;
		bool has_more() const;
		bool get_more();

		const json& result() const;

	private:
		struct impl;
		std::shared_ptr<impl> p;
		query_cursor(std::shared_ptr<impl> p);
		friend class database;
};

} // namespace arango

#endif // ARANGO_QUERY_CURSOR_H
