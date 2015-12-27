#ifndef DATABASE_PRIVATE_H
#define DATABASE_PRIVATE_H

#include "database.h"
#include <cpr/cpr.h>

namespace arango {
struct database::impl {
		std::string host;
		std::string database;
		std::string username;
		std::string password;

		std::string getUrl(const std::string &postfix) {
			return host + "/_db/" + database + "/_api/" + postfix;
		}

		json read(const std::string &url) {
			json document;

			auto response = cpr::Get(cpr::Url{url},
															 cpr::Authentication{username, password});
			if(response.status_code == 200) {
				document = json::parse(response.text);
			}

			return document;
		}

		bool create(const std::string &url, json &document, cpr::Parameters parameters, std::string response_tag = "") {
			bool result = false;

			auto response = cpr::Post(cpr::Url{url},
																cpr::Authentication{username, password},
																parameters,
																cpr::Body{document.dump(0)});
			if(response.status_code == 202) {
				auto respDoc = json::parse(response.text);

				json &d = respDoc;
				if(response_tag.empty()) {
					d = respDoc;
				}
				else {
					d = respDoc[response_tag];
				}

				document["_id"] = d["_id"];
				document["_key"] = d["_key"];
				document["_rev"] = d["_rev"];

				result = true;
			}

			return result;
		}

		bool replace(const std::string &url, json &document, std::string response_tag = "") {
			bool result = false;

			auto response = cpr::Put(cpr::Url{url},
															 cpr::Authentication{username, password},
															 cpr::Body{document.dump(0)});
			if(response.status_code == 202) {
				auto respDoc = json::parse(response.text);

				json &d = respDoc;
				if(response_tag.empty()) {
					d = respDoc;
				}
				else {
					d = respDoc[response_tag];
				}

				document["_id"] = d["_id"];
				document["_key"] = d["_key"];
				document["_rev"] = d["_rev"];

				result = true;
			}

			return result;
		}

		bool patch(const std::string &url, const json &document) {
			bool result = false;

			auto response = cpr::Patch(cpr::Url{url},
																 cpr::Authentication{username, password},
																 cpr::Body{document.dump(0)});
			if(response.status_code == 202) {
				result = true;
			}

			return result;
		}

		bool remove(const std::string &url) {
			bool result = false;

			auto response = cpr::Delete(cpr::Url{url},
																	cpr::Authentication{username, password});
			if(response.status_code == 202) {
				result = true;
			}

			return result;
		}
};
}

#endif // DATABASE_PRIVATE_H
