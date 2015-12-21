#include "query_cursor.h"

#include <cpr/cpr.h>

#include "query_cursor_private.h"

namespace arango {


query_cursor::query_cursor(std::shared_ptr<impl> p) : p(p)
{

}

bool query_cursor::is_valid() const
{
	return !p->result.is_null();
}

bool query_cursor::has_more() const
{
	return is_valid() && p->result["hasMore"].get<bool>();
}

bool query_cursor::get_more()
{
	bool result = false;

	if(has_more()) {
		result = p->get_more();
	}

	return result;
}

const json &query_cursor::result() const
{
	return p->result["result"];
}

} // namespace arango
