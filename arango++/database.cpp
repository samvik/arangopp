
#include "database_private.h"

#include "query_cursor_private.h"
#include <boost/lexical_cast.hpp>

namespace arango {

database::database(const std::string &host, const std::string &username,
									 const std::string &password, const std::string &database)
	: p(new database::impl)
{
	p->host = host;
	p->username = username;
	p->password = password;
	p->database = database;
}

database::~database()
{
	delete p;
}

json database::create_collection(json properties)
{
	auto response = cpr::Post(
				cpr::Authentication{p->username, p->password},
				cpr::Url{p->getUrl("collection")},
				cpr::Body(properties.dump(0)));

	return json::parse(response.text);
}

json database::drop_collection(const std::string &name)
{
	auto response = cpr::Delete(
				cpr::Authentication{p->username, p->password},
				cpr::Url{p->getUrl("collection/" + name)});

	return json::parse(response.text);
}

json database::truncate_collection(const std::string &name)
{
	auto response = cpr::Put(
				cpr::Authentication{p->username, p->password},
				cpr::Url{p->getUrl("collection/" + name + "/truncate")});

	return json::parse(response.text);
}

query_cursor database::query(const std::string &q, unsigned batch_size)
{
	auto create_cursor = [this, q, batch_size]() {

		json queryDocument = {
			{"query", q},
			{"count", true},
			{"batchSize", batch_size}
		};

		auto response = cpr::Post(cpr::Url{p->getUrl("cursor")},
															cpr::Authentication{p->username, p->password},
															cpr::Body{queryDocument.dump(0)});

		return json::parse(response.text);
	};

	auto read_next = [this](const std::string &cursor_id) {
		auto response = cpr::Put(cpr::Url{p->getUrl("cursor/" + cursor_id)},
														 cpr::Authentication{p->username, p->password});

		return json::parse(response.text);
	};

	auto delete_cursor = [this](const std::string &cursor_id) {
		auto response = cpr::Delete(cpr::Url{p->getUrl("cursor/" + cursor_id)},
															 cpr::Authentication{p->username, p->password});

		return json::parse(response.text);
	};

	return query_cursor(std::make_shared<query_cursor::impl>(create_cursor,
																													 read_next,
																													 delete_cursor));
}

} // namespace arango
