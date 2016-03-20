#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <arango++/database.h>

class DatabaseFixture {
	public:
		DatabaseFixture() : dbName("myDatabase"), host("http://localhost:8529")
		{
			arango::database database(host, "root", "password");
			arango::json dbCreateResult = database.create(dbName, "username", "password");
			CHECK_FALSE(dbCreateResult["error"].get<bool>());
		}

		~DatabaseFixture()
		{
			arango::database database(host, "root", "password");
			arango::json dbDropResult = database.drop(dbName);
			CHECK_FALSE(dbDropResult["error"].get<bool>());
		}
	protected:
		std::string dbName;
		std::string host;
};

TEST_CASE_METHOD(DatabaseFixture, "create and drop collection", "[database][collection]" )
{
	arango::database database(host, "username", "password", dbName);
	auto createResult = database.create_collection(
			arango::json{{"name", "myCollection"}});
	CHECK_FALSE(createResult["error"].get<bool>());

	auto collectionList = database.list_collections(true);
	CHECK_FALSE(collectionList["error"].get<bool>());
	CHECK(collectionList["names"].count("myCollection") == 1);

	auto dropResult = database.drop_collection("myCollection");
	CHECK_FALSE(dropResult["error"].get<bool>());
}

TEST_CASE_METHOD(DatabaseFixture, "create and drop graph", "[database][graph]" )
{
	arango::database database(host, "username", "password", dbName);

	auto graphDef =  arango::json{
			{"name", "myGraph"},
			{"edgeDefinitions",
					{
		         {
				         {"collection", "myEdges"},
				         {"from", {"myVertex1"}},
				         {"to", {"myVertex2"}}
		         }
					}
			},
			{"orphanCollections", ""}
	};
	auto createResult = database.create_graph(graphDef);
	CHECK_FALSE(createResult["error"].get<bool>());

	auto graphList = database.list_graphs();
	std::cout << graphList << std::endl;
	CHECK(graphList["graphs"][0]["_key"].get<std::string>() == "myGraph");

	auto dropResult = database.drop_graph("myGraph", true);
	CHECK_FALSE(dropResult["error"].get<bool>());
}