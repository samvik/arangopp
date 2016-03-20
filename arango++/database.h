#ifndef ARANGO_DATABASE_H
#define ARANGO_DATABASE_H

#include "json.h"
#include "query_cursor.h"

namespace arango {

class database
{
	public:
		database(const std::string &host, const std::string &username,
						 const std::string &password, const std::string &database = "_system");

		virtual ~database();

		json create(const std::string &database, const std::string &username, const std::string &password);
		json drop(const std::string &database);

		json list_collections(bool excludeSystem = true);
		json create_collection(json properties);
		json drop_collection(const std::string &name);
		json truncate_collection(const std::string &name);

		json list_graphs();
		json create_graph(json properties) const;
		json get_graph(const std::string &graph) const;
		json drop_graph(const std::string &graph, bool drop_collections = true) const;

		json get_collection(const std::string &name);
		json get_collection_properties(const std::string &name);
		json get_collection_count(const std::string &name);
		json get_collection_statisitcs(const std::string &name);
		json get_collection_revision_id(const std::string &name);
		json get_collection_checksum(const std::string &name);

		query_cursor query(const std::string &q, unsigned batch_size = 128);
		query_cursor query(const std::string &q, const json &bindVars, unsigned batch_size = 128);

		json list_functions(std::string namespace_ = "");
		json create_function(std::string name, std::string code, bool isDeterministic = true);
		json remove_function(std::string name, bool group = false);

	protected:
		struct impl;
		impl *p;
};

} // namespace arango

#endif // ARANGO_DATABASE_H
