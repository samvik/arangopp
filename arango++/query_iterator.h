#ifndef ARANGO_QUERY_ITERATOR_H
#define ARANGO_QUERY_ITERATOR_H

#include "json.h"

#include <boost/iterator/iterator_facade.hpp>

namespace arango {

template <class Value>
class query_iterator_base
		: public boost::iterator_facade<query_iterator_base<Value>, Value, boost::forward_traversal_tag>
{
	public:
		typedef std::function<json()> create_cursor_func;
		typedef std::function<json(const std::string&)> read_next_func;
		typedef std::function<bool(const std::string&)> delete_cursor_func;

		query_iterator_base(): m_position(-1) {
		}

		query_iterator_base(create_cursor_func create_cursor,
												read_next_func read_next,
												delete_cursor_func delete_cursor)
			: m_create_cursor(create_cursor), m_read_next(read_next),
				m_delete_cursor(delete_cursor)
		{
			m_result_set = m_create_cursor();
			if(m_result_set.size() > 0) {
				m_position = 0;
			}
			else {
				m_position = -1;
			}
		}

//		template <class OtherValue>
//		query_iterator_base(query_iterator_base<OtherValue> const& other)
//			: m_node(other.m_node) {}

	private:
		friend class boost::iterator_core_access;
		template <class> friend class query_iterator_base;

		template <class OtherValue>
		bool equal(query_iterator_base<OtherValue> const& other) const
		{
			return m_position == -1 && other.m_position == -1;
		}

		void increment()
		{
			++m_position;

			const json &result = m_result_set.at("result");
			if(m_position >= result.size()) {
				if(m_result_set["hasMore"].get<bool>()) {

					//std::cout << m_result_set << std::endl;
					m_result_set = m_read_next(m_result_set["id"].get<std::string>());
					m_position = 0;
				}
				else {
					m_position = -1;
				}
			}
		}

		Value& dereference() const
		{
			const json &result = m_result_set.at("result");
			return result[m_position];
		}

		create_cursor_func m_create_cursor;
		read_next_func m_read_next;
		delete_cursor_func m_delete_cursor;

		int m_position;
		json m_result_set;
};

typedef query_iterator_base<const json> const_query_iterator;


} // namespace arango

#endif // ARANGO_QUERY_ITERATOR_H
