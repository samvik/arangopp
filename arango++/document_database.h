#ifndef ARANGO_DOCUMENT_DATABASE_H
#define ARANGO_DOCUMENT_DATABASE_H

#include "database.h"

namespace arango {

class document_database : public database
{
public:
		document_database(const std::string &host, const std::string &username,
											const std::string &password, const std::string &db);

		json read_document(const std::string &id);
		json create_document(const std::string &collection, const json &document);
		json replace_document(const std::string &id, const json &document);
		json patch_document(const std::string &id, const json &document);
		json remove_document(const std::string &id);

		json read_edge(const std::string &id);
		json create_edge(const std::string &collection, const json &document,
										 const json &from, const json &to);
		json replace_edge(const std::string &id, const json &document);
		json patch_edge(const std::string &id, const json &document);
		json remove_edge(const std::string &id);
};

} // namespace arango

#endif // ARANGO_DOCUMENT_DATABASE_H
