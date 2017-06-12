#include "query_cursor.h"

#include <cpr/cpr.h>

#include "query_cursor_private.h"

namespace arango
{

query_cursor::query_cursor(std::shared_ptr<impl> p) : p(p)
{
}

bool query_cursor::has_more() const
{
    return p->result.is_null() || p->result["hasMore"].get<bool>();
}

bool query_cursor::get_more()
{
    bool result = false;

    if(has_more())
    {
        result = p->get_more();
    }

    return result;
}

int query_cursor::count() const
{
    int c = -1;
    if(p->result)
    {
        c = p->result["count"];
    }
    return c;
}

int query_cursor::batch_size() const
{
    return result().size();
}

const json &query_cursor::result() const
{
    return p->result["result"];
}

const json &query_cursor::first()
{
    json *result = nullptr;
    if(get_more())
    {
        result = &p->result["result"][0];
    }
    return *result;
}

const_query_iterator query_cursor::begin() const
{
    return const_query_iterator(p->create_cursor, p->read_next,
                                p->delete_cursor);
}

const_query_iterator query_cursor::end() const
{
    return const_query_iterator();
}

} // namespace arango
