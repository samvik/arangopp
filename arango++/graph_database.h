#ifndef ARANGO_GRAPH_DATABASE_H
#define ARANGO_GRAPH_DATABASE_H

#include "database.h"

namespace arango {

class graph_database : public database
{
	public:
		graph_database(const std::string &host, const std::string &username,
									 const std::string &password, const std::string &db,
									 const std::string &graph);

		~graph_database();

		json read_vertex(const std::string &id);
		bool create_vertex(const std::string &collection, json &document);
		bool replace_vertex(const std::string &id, json &document);
		bool patch_vertex(const std::string &id, const json &document);
		bool remove_vertex(const std::string &id);

		json read_edge(const std::string &id);
		bool create_edge(const std::string &collection,
													 json &document,
													 const json &from_document, const json &to_document);
		bool replace_edge(const std::string &id, json &document);
		bool patch_edge(const std::string &id, const json &document);
		bool remove_edge(const std::string &id);

	private:
		struct impl;
		impl *p;
};

} // namespace arango

#endif // ARANGO_GRAPH_DATABASE_H
