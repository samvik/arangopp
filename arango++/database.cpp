
#include "database_private.h"

#include "query_cursor_private.h"
#include <boost/lexical_cast.hpp>

namespace arango {

database::database(const std::string &host, const std::string &username,
									 const std::string &password, const std::string &database)
	: p(new database::impl(host, database, username, password))
{
}

database::~database()
{
	delete p;
}


json database::list() {
	auto response = cpr::Get(
			p->authentication,
			cpr::Url{p->getUrl("database")});
	return database::p->validateResponse(response);
}


json database::list_accessible() {
	auto response = cpr::Get(
			p->authentication,
			cpr::Url{p->getUrl("database/user")});
	return database::p->validateResponse(response);
}

json database::create(const std::string &database, const std::string &username, const std::string &password)
{

	json parameters = {
			{"name", database},
			{
					"users",
					{
							{{"username", username},
							{"passwd", password},
							{"active", true}}
					}
			}
	};

	auto response = cpr::Post(
			p->authentication,
			cpr::Url{p->getUrl("database")},
			cpr::Body(parameters.dump(0)));
	return database::p->validateResponse(response);
}

json database::drop(const std::string &database)
{
	auto response = cpr::Delete(
			p->authentication,
			cpr::Url{p->getUrl("database/" + database)});
	return database::p->validateResponse(response);
}


json database::list_collections(bool excludeSystem)
{
	auto response = cpr::Get(
				p->authentication,
				cpr::Url{p->getUrl("collection")},
				cpr::Parameters{{"excludeSystem", excludeSystem?"true":"false"}});
	return database::p->validateResponse(response);
}

json database::create_collection(json properties)
{
	auto response = cpr::Post(
				p->authentication,
				cpr::Url{p->getUrl("collection")},
				cpr::Body(properties.dump(0)));
	return database::p->validateResponse(response);
}

json database::drop_collection(const std::string &name)
{
	auto response = cpr::Delete(
				p->authentication,
				cpr::Url{p->getUrl("collection/" + name)});
	return database::p->validateResponse(response);
}

json database::truncate_collection(const std::string &name)
{
	auto response = cpr::Put(
				p->authentication,
				cpr::Url{p->getUrl("collection/" + name + "/truncate")});
	return database::p->validateResponse(response);
}

json database::list_graphs()
{
	auto response = cpr::Get(cpr::Url{database::p->getUrl("gharial")},
	                         database::p->authentication);
	return database::p->validateResponse(response);
}

json database::create_graph(json properties) const
{
	auto response = cpr::Post(cpr::Url{database::p->getUrl("gharial")},
	                          database::p->authentication,
	                          cpr::Body{properties.dump(0)});
	return database::p->validateResponse(response);
}

json database::get_graph(const std::string &graph) const
{
	auto response = cpr::Get(cpr::Url{database::p->getUrl("gharial/" + graph)},
	                         database::p->authentication);
	return database::p->validateResponse(response);
}

json database::drop_graph(const std::string &graph, bool drop_collections) const
{
	auto response = cpr::Delete(cpr::Url{database::p->getUrl("gharial/" + graph)},
	                            database::p->authentication,
	                            cpr::Parameters{{"dropCollections", drop_collections?"true":"false"}});
	return database::p->validateResponse(response);
}

json database::get_collection(const std::string &name)
{
	auto response = cpr::Get(
				p->authentication,
				cpr::Url{p->getUrl("collection/" + name)});
	return database::p->validateResponse(response);
}

json database::get_collection_properties(const std::string &name)
{
	auto response = cpr::Get(
				p->authentication,
				cpr::Url{p->getUrl("collection/" + name + "/properties")});
	return database::p->validateResponse(response);
}

json database::get_collection_count(const std::string &name)
{
	auto response = cpr::Get(
				p->authentication,
				cpr::Url{p->getUrl("collection/" + name + "/count")});
	return database::p->validateResponse(response);
}

json database::get_collection_statisitcs(const std::string &name)
{
	auto response = cpr::Get(
				p->authentication,
				cpr::Url{p->getUrl("collection/" + name + "/figures")});
	return database::p->validateResponse(response);
}

json database::get_collection_revision_id(const std::string &name)
{
	auto response = cpr::Get(
				p->authentication,
				cpr::Url{p->getUrl("collection/" + name + "/revision")});
	return database::p->validateResponse(response);
}

json database::get_collection_checksum(const std::string &name)
{
	auto response = cpr::Get(
				p->authentication,
				cpr::Url{p->getUrl("collection/" + name + "/checksum")});
	return database::p->validateResponse(response);
}

query_cursor database::query(const std::string &q, unsigned batch_size)
{
	return query(q, json(), batch_size);
}

query_cursor database::query(const std::string &q, const json &bindVars, unsigned batch_size)
{
	auto create_cursor = [this, q, bindVars, batch_size]() {

		json queryDocument = {
			{"query", q},
			{"count", true},
			{"batchSize", batch_size}
		};

		if(!bindVars.is_null()) {
			queryDocument["bindVars"] = bindVars;
		}

		auto response = cpr::Post(cpr::Url{p->getUrl("cursor")},
															p->authentication,
															cpr::Body{queryDocument.dump(0)});
		return database::p->validateResponse(response);
	};

	auto read_next = [this](const std::string &cursor_id) {
		auto response = cpr::Put(cpr::Url{p->getUrl("cursor/" + cursor_id)},
														 p->authentication);
		return database::p->validateResponse(response);
	};

	auto delete_cursor = [this](const std::string &cursor_id) {
		auto response = cpr::Delete(cpr::Url{p->getUrl("cursor/" + cursor_id)},
															 p->authentication);
		return database::p->validateResponse(response);
	};

	return query_cursor(std::make_shared<query_cursor::impl>(create_cursor,
																													 read_next,
																													 delete_cursor));
}

json database::list_functions(std::string namespace_)
{
	cpr::Parameters parameters;
	if(!namespace_.empty()) {
		parameters.AddParameter({"namespace", namespace_});
	}

	auto response = cpr::Get(cpr::Url{p->getUrl("aqlfunction")},
															parameters,
															p->authentication);
	return database::p->validateResponse(response);
}

json database::create_function(std::string name, std::string code, bool isDeterministic)
{
	json parameters = {
		{"isDeterministic", isDeterministic},
		{"code", code},
		{"name", name}
	};

	auto response = cpr::Post(cpr::Url{p->getUrl("aqlfunction")},
														p->authentication,
														cpr::Body{parameters.dump(0)});
	return database::p->validateResponse(response);
}

json database::remove_function(std::string name, bool group)
{
	auto response = cpr::Delete(cpr::Url{p->getUrl("aqlfunction/" + name)},
															cpr::Parameters{{"group", group?"true":"false"}},
															p->authentication);
	return database::p->validateResponse(response);
}

} // namespace arango
