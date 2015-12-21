
#include "database.h"

#include <cpr/cpr.h>
#include "query_cursor_private.h"

#include <boost/lexical_cast.hpp>

namespace arango {

struct database::impl {
		std::string host;
		std::string database;

		std::string getUrl(const std::string &postfix) {
			return host + "/_db/" + database + "/_api/" + postfix;
		}
};

database::database(const std::string &host, const std::string &database)
	: p(new database::impl)
{
	p->host = host;
	p->database = database;
}

json database::read_document(const std::string &id)
{
	json document;

	auto response = cpr::Get(cpr::Url{p->getUrl("document/" + id)});
	if(response.status_code == 200) {
		document = json::parse(response.text);
	}

	return document;
}

bool database::create_document(const std::string &collection, json &document)
{
	bool result = false;

	auto response = cpr::Post(cpr::Url{p->getUrl("document")},
														cpr::Parameters{{"collection", collection}},
														cpr::Body{document.dump(0)});
	if(response.status_code == 202) {
		auto respDoc = json::parse(response.text);
		document["_id"] = respDoc["_id"];
		document["_key"] = respDoc["_key"];
		document["_rev"] = respDoc["_rev"];

		result = true;
	}

	return result;
}

bool database::replace_document(const std::string &id, json &document)
{
	bool result = false;

	auto response = cpr::Put(cpr::Url{p->getUrl("document/" + id)},
														cpr::Body{document.dump(0)});
	if(response.status_code == 202) {
		auto respDoc = json::parse(response.text);
		document["_id"] = respDoc["_id"];
		document["_key"] = respDoc["_key"];
		document["_rev"] = respDoc["_rev"];

		result = true;
	}

	return result;
}

bool database::patch_document(const std::string &id, const json &document)
{
	bool result = false;

	auto response = cpr::Patch(cpr::Url{p->getUrl("document/" + id)},
														cpr::Body{document.dump(0)});
	if(response.status_code == 202) {
		result = true;
	}

	return result;
}

bool database::remove_document(const std::string &id)
{
	bool result = false;

	auto response = cpr::Delete(cpr::Url{p->getUrl("document/" + id)});
	if(response.status_code == 202) {
		result = true;
	}

	return result;
}

json database::read_edge(const std::__cxx11::string &id)
{
	json edge;

	auto response = cpr::Get(cpr::Url{p->getUrl("edge/" + id)});
	if(response.status_code == 200) {
		edge = json::parse(response.text);
	}

	return edge;
}

bool database::create_edge(const std::string &collection,
													 json &edge, const json &from_document, const json &to_document)
{
	bool result = false;

	auto response = cpr::Post(cpr::Url{p->getUrl("edge")},
														cpr::Parameters{{"collection", collection},
																						{"from", from_document.at("_id").get<std::string>()},
																						{"to", to_document.at("_id").get<std::string>()}},
														cpr::Body{edge.dump(0)});
	if(response.status_code == 202) {
		auto respDoc = json::parse(response.text);
		edge["_id"] = respDoc["_id"];
		edge["_key"] = respDoc["_key"];
		edge["_rev"] = respDoc["_rev"];

		result = true;
	}

	return result;
}

bool database::replace_edge(const std::__cxx11::string &id, json &edge)
{
	bool result = false;

	auto response = cpr::Put(cpr::Url{p->getUrl("edge/" + id)},
														cpr::Body{edge.dump(0)});
	if(response.status_code == 202) {
		auto respDoc = json::parse(response.text);
		edge["_id"] = respDoc["_id"];
		edge["_key"] = respDoc["_key"];
		edge["_rev"] = respDoc["_rev"];

		result = true;
	}

	return result;
}

bool database::patch_edge(const std::__cxx11::string &id, const json &edge)
{
	bool result = false;

	auto response = cpr::Patch(cpr::Url{p->getUrl("edge/" + id)},
														cpr::Body{edge.dump(0)});
	if(response.status_code == 202) {
		result = true;
	}

	return result;
}

bool database::remove_edge(const std::__cxx11::string &id)
{
	bool result = false;

	auto response = cpr::Delete(cpr::Url{p->getUrl("edge/" + id)});
	if(response.status_code == 202) {
		result = true;
	}

	return result;
}

query_cursor database::query(const std::string &q)
{
	json queryDocument = {{"query", q}, {"count", true}, {"batchSize", 3}};
	auto response = cpr::Post(cpr::Url{p->getUrl("cursor")}, cpr::Body{queryDocument.dump(0)});
	json result = json::parse(response.text);

	auto get_more_f = [this, result]() {
		std::string id = result.at("id").get<std::string>();
		auto response = cpr::Put(cpr::Url{p->getUrl("cursor/" + id)});
		auto newResult = json::parse(response.text);
		return newResult;
	};

	return query_cursor(std::make_shared<query_cursor::impl>(result, get_more_f));
}

} // namespace arango
