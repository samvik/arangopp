#ifndef ARANGO_DATABASE_H
#define ARANGO_DATABASE_H

#include "json.h"
#include "query_cursor.h"

namespace arango {

class database
{
	public:
		database(const std::string &host, const std::__cxx11::string &username, const std::__cxx11::string &password, const std::string &database);

		json read_document(const std::string &id);
		bool create_document(const std::string &collection, json &document);
		bool replace_document(const std::string &id, json &document);
		bool patch_document(const std::string &id, const json &document);
		bool remove_document(const std::string &id);

		json read_edge(const std::string &id);
		bool create_edge(const std::string &collection, json &edge,
										 const json &from_document, const json &to_document);
		bool replace_edge(const std::string &id, json &edge);
		bool patch_edge(const std::string &id, const json &edge);
		bool remove_edge(const std::string &id);

		query_cursor query(const std::string &q);

	private:
		struct impl;
		impl *p;
};

} // namespace arango

#endif // ARANGO_DATABASE_H
