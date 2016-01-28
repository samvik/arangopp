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
	auto response = cpr::Get(cpr::Url{database::p->getUrl("document/" + id)},
													 database::p->authentication);
	database::p->validateResponse(response);
	return json::parse(response.text);
}

json document_database::create_document(const std::string &collection, const json &document)
{
	auto response = cpr::Post(cpr::Url{database::p->getUrl("document")},
														database::p->authentication,
														cpr::Parameters{{"collection", collection}},
														cpr::Body{document.dump(0)});
	database::p->validateResponse(response);
	return json::parse(response.text);
}

json document_database::replace_document(const std::string &id, const json &document)
{
	auto response = cpr::Put(cpr::Url{database::p->getUrl("document/" + id)},
													 database::p->authentication,
													 cpr::Body{document.dump(0)});
	database::p->validateResponse(response);
	return json::parse(response.text);
}

json document_database::patch_document(const std::string &id, const json &document)
{
	auto response = cpr::Patch(cpr::Url{database::p->getUrl("document/" + id)},
													 database::p->authentication,
													 cpr::Body{document.dump(0)});
	database::p->validateResponse(response);
	return json::parse(response.text);
}

json document_database::remove_document(const std::string &id)
{
	auto response = cpr::Delete(cpr::Url{database::p->getUrl("document/" + id)},
													 database::p->authentication);
	database::p->validateResponse(response);
	return json::parse(response.text);
}

json document_database::read_edge(const std::string &id)
{
	auto response = cpr::Get(cpr::Url{database::p->getUrl("edge/" + id)},
													 database::p->authentication);
	database::p->validateResponse(response);
	return json::parse(response.text);
}

json document_database::create_edge(const std::string &collection,
													 const json &document, const json &from,
													 const json &to)
{
	auto parameters = cpr::Parameters{
		{"collection", collection},
		{"from", from.at("_id").get<std::string>()},
		{"to", to.at("_id").get<std::string>()}
	};

	auto response = cpr::Post(cpr::Url{database::p->getUrl("edge")},
														database::p->authentication,
														parameters,
														cpr::Body{document.dump(0)});
	database::p->validateResponse(response);
	return json::parse(response.text);
}

json document_database::replace_edge(const std::string &id, const json &document)
{
	auto response = cpr::Put(cpr::Url{database::p->getUrl("edge/" + id)},
													 database::p->authentication,
													 cpr::Body{document.dump(0)});
	database::p->validateResponse(response);
	return json::parse(response.text);
}

json document_database::patch_edge(const std::string &id, const json &document)
{
	auto response = cpr::Patch(cpr::Url{database::p->getUrl("edge/" + id)},
													 database::p->authentication,
													 cpr::Body{document.dump(0)});
	database::p->validateResponse(response);
	return json::parse(response.text);
}

json document_database::remove_edge(const std::string &id)
{
	auto response = cpr::Delete(cpr::Url{database::p->getUrl("edge/" + id)},
													 database::p->authentication);
	database::p->validateResponse(response);
	return json::parse(response.text);
}

} // namespace arango
