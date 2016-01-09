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

		json list_graphs();

		json create_graph(json properties);
		json get_graph(const std::string &graph);
		json drop_graph(const std::string &graph, bool drop_collections = true);

		json read_vertex(const std::string &id);
		json create_vertex(const std::string &collection, const json &document);
		json replace_vertex(const std::string &id, const json &document);
		json patch_vertex(const std::string &id, const json &document);
		json remove_vertex(const std::string &id);

		json read_edge(const std::string &id);
		json create_edge(const std::string &collection, json document,
													 const json &from, const json &to);
		json create_edge(const std::string &collection, const json &document);
		json replace_edge(const std::string &id, json &document);
		json patch_edge(const std::string &id, const json &document);
		json remove_edge(const std::string &id);

	private:
		struct impl;
		impl *p;
};

} // namespace arango

#endif // ARANGO_GRAPH_DATABASE_H
