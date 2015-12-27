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
		bool create_document(const std::string &collection, json &document);
		bool replace_document(const std::string &id, json &document);
		bool patch_document(const std::string &id, const json &document);
		bool remove_document(const std::string &id);

		json read_edge(const std::string &id);
		bool create_edge(const std::string &collection, json &edge,
										 const json &from_document, const json &to_document);
		bool replace_edge(const std::string &id, json &edge);
		bool patch_edge(const std::string &id, const json &edge);
		bool remove_edge(const std::string &id);
};

} // namespace arango

#endif // ARANGO_DOCUMENT_DATABASE_H
