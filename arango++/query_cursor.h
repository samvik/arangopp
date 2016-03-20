#ifndef ARANGO_QUERY_CURSOR_H
#define ARANGO_QUERY_CURSOR_H

#include <memory>
#include "json.h"

#include "query_iterator.h"

namespace arango {

class query_cursor
{
	public:
		bool has_more() const;
		bool get_more();

		int count() const;
		int batch_size() const;

		const json& result() const;

		const json& first();

		const_query_iterator begin() const;
		const_query_iterator end() const;

	private:
		struct impl;
		std::shared_ptr<impl> p;
		query_cursor(std::shared_ptr<impl> p);
		friend class database;
};

} // namespace arango

#endif // ARANGO_QUERY_CURSOR_H
