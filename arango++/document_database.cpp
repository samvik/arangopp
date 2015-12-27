#include "document_database.h"
#include "database_private.h"

namespace arango {

document_database::document_database(const std::string &host, const std::string &username,
																		 const std::string &password, const std::string &db) :
	database(host, username, password, db)
{

}

json document_database::read_document(const std::string &id)
{
	return database::p->read(database::p->getUrl("document/" + id));
}

bool document_database::create_document(const std::string &collection, json &document)
{
	auto parameters = cpr::Parameters{{"collection", collection}};
	return database::p->create(database::p->getUrl("document"), document, parameters);
}

bool document_database::replace_document(const std::string &id, json &document)
{
	return database::p->replace(database::p->getUrl("document/" + id), document);
}

bool document_database::patch_document(const std::string &id, const json &document)
{
	return database::p->patch(database::p->getUrl("document/" + id), document);
}

bool document_database::remove_document(const std::string &id)
{
	return database::p->remove(database::p->getUrl("document/" + id));
}

json document_database::read_edge(const std::string &id)
{
	return database::p->read(database::p->getUrl("edge/" + id));
}

bool document_database::create_edge(const std::string &collection,
													 json &edge, const json &from_document,
													 const json &to_document)
{
	auto parameters = cpr::Parameters{
		{"collection", collection},
		{"from", from_document.at("_id").get<std::string>()},
		{"to", to_document.at("_id").get<std::string>()}
	};

	return database::p->create(database::p->getUrl("edge"), edge, parameters);
}

bool document_database::replace_edge(const std::string &id, json &edge)
{
	return database::p->replace(database::p->getUrl("edge/" + id), edge);
}

bool document_database::patch_edge(const std::string &id, const json &edge)
{
	return database::p->patch(database::p->getUrl("edge/" + id), edge);
}

bool document_database::remove_edge(const std::string &id)
{
	return database::p->remove(database::p->getUrl("edge/" + id));
}

} // namespace arango
