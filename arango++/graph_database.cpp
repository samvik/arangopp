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

std::string graph_database::graph_name() const
{
	return p->graph;
}

json graph_database::read_vertex(const std::string &id)
{
	auto response = cpr::Get(cpr::Url{database::p->getUrl("gharial/" + p->graph + "/vertex/" + id)},
													 database::p->authentication);
	database::p->validateResponse(response);
	return json::parse(response.text)["vertex"];
}

json graph_database::create_vertex( const std::string &collection,
																	 const json &document)
{
	auto response = cpr::Post(cpr::Url{database::p->getUrl("gharial/" + p->graph + "/vertex/" + collection)},
														database::p->authentication,
														cpr::Body{document.dump(0)});
	database::p->validateResponse(response);
	return json::parse(response.text)["vertex"];
}

json graph_database::replace_vertex(const std::string &id, const json &document)
{
	auto response = cpr::Put(cpr::Url{database::p->getUrl("gharial/" + p->graph + "/vertex/" + id)},
													 database::p->authentication,
													 cpr::Body{document.dump(0)});
	database::p->validateResponse(response);
	return json::parse(response.text)["vertex"];
}

json graph_database::patch_vertex(const std::string &id, const json &document)
{
	auto response = cpr::Patch(cpr::Url{database::p->getUrl("gharial/" + p->graph + "/vertex/" + id)},
													 database::p->authentication,
													 cpr::Body{document.dump(0)});
	database::p->validateResponse(response);
	return json::parse(response.text)["vertex"];
}

json graph_database::remove_vertex(const std::string &id)
{
	auto response = cpr::Delete(cpr::Url{database::p->getUrl("gharial/" + p->graph + "/vertex/" + id)},
													 database::p->authentication);
	database::p->validateResponse(response);
	return json::parse(response.text);
}

json graph_database::read_edge(const std::string &id)
{
	auto response = cpr::Get(cpr::Url{database::p->getUrl("gharial/" + p->graph + "/edge/" + id)},
													 database::p->authentication);
	database::p->validateResponse(response);
	return json::parse(response.text)["edge"];
}

json graph_database::create_edge(const std::string &collection, json document,
																 const json &from, const json &to)
{
	document["_to"] = to["_id"];
	document["_from"] = from["_id"];

	return create_edge(collection, document);
}

json graph_database::create_edge(const std::string &collection, const json &document)
{
	auto response = cpr::Post(cpr::Url{database::p->getUrl("gharial/" + p->graph + "/edge/" + collection)},
														database::p->authentication,
														cpr::Body{document.dump(0)});
	database::p->validateResponse(response);
	return json::parse(response.text)["edge"];
}

json graph_database::replace_edge(const std::string &id, json &document)
{
	auto response = cpr::Put(cpr::Url{database::p->getUrl("gharial/" + p->graph + "/edge/" + id)},
													 database::p->authentication,
													 cpr::Body{document.dump(0)});
	database::p->validateResponse(response);
	return json::parse(response.text)["edge"];
}

json graph_database::patch_edge(const std::string &id, const json &document)
{
	auto response = cpr::Patch(cpr::Url{database::p->getUrl("gharial/" + p->graph + "/edge/" + id)},
													 database::p->authentication,
													 cpr::Body{document.dump(0)});
	database::p->validateResponse(response);
	return json::parse(response.text)["edge"];
}

json graph_database::remove_edge(const std::string &id)
{
	auto response = cpr::Delete(cpr::Url{database::p->getUrl("gharial/" + p->graph + "/edge/" + id)},
													 database::p->authentication);
	database::p->validateResponse(response);
	return json::parse(response.text);
}

} // namespace arango
