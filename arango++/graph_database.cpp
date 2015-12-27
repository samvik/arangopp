#include "graph_database.h"
#include "database_private.h"

namespace arango {

struct graph_database::impl {
		std::string graph;
};

graph_database::graph_database(const std::string &host, const std::string &username,
															 const std::string &password, const std::string &db,
															 const std::string &graph) :
	database(host, username, password, db), p(new impl)
{
	p->graph = graph;
}

graph_database::~graph_database()
{
	delete p;
}

json graph_database::read_vertex(const std::string &id)
{
	return database::p->read(database::p->getUrl("gharial/" + p->graph + "/vertex/" + id))["vertex"];
}

bool graph_database::create_vertex( const std::string &collection,
																	 json &document)
{
	auto parameters = cpr::Parameters{};
	return database::p->create(database::p->getUrl("gharial/" + p->graph + "/vertex/" + collection),
									 document, parameters, "vertex");
}

bool graph_database::replace_vertex(const std::string &id, json &document)
{
	return database::p->replace(database::p->getUrl("gharial/" + p->graph + "/vertex/" + id),
										document, "vertex");
}

bool graph_database::patch_vertex(const std::string &id, const json &document)
{
	return database::p->patch(database::p->getUrl("gharial/" + p->graph + "/vertex/" + id), document);
}

bool graph_database::remove_vertex(const std::string &id)
{
	return database::p->remove(database::p->getUrl("gharial/" + p->graph + "/vertex/" + id));
}

json graph_database::read_edge(const std::string &id)
{
	return database::p->read(database::p->getUrl("gharial/" + p->graph + "/edge/" + id))["edge"];
}

bool graph_database::create_edge(const std::string &collection,
																 json &document,
																 const json &from_document,
																 const json &to_document)
{
	auto parameters = cpr::Parameters{};

	document["_to"] = to_document.at("_id").get<std::string>();
	document["_from"] = from_document.at("_id").get<std::string>();

	return database::p->create(database::p->getUrl("gharial/" + p->graph + "/edge/" + collection),
									 document, parameters, "edge");
}

bool graph_database::replace_edge(const std::string &id, json &document)
{
	return database::p->replace(database::p->getUrl("gharial/" + p->graph + "/edge/" + id),
										document, "edge");
}

bool graph_database::patch_edge(const std::string &id, const json &document)
{
	return database::p->patch(database::p->getUrl("gharial/" + p->graph + "/edge/" + id), document);
}

bool graph_database::remove_edge(const std::string &id)
{
	return database::p->remove(database::p->getUrl("gharial/" + p->graph + "/edge/" + id));
}

} // namespace arango
