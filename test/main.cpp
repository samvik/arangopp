#include <iostream>
#include <boost/lexical_cast.hpp>
#include "arango++/graph_database.h"
#include "arango++/document_database.h"

int main(int argc, char **argv) {
	//arango::database db("http://localhost:8529", "gen", "gen", "gen");

//	// Create document
//	arango::json doc0{{"name", "John Doe"}};
//	db.create_document("persona", doc0);

//	// Read document
//	auto doc1 = db.read_document(doc0["_id"]);
//	std::cout << doc1 << std::endl;

//	// Replace document
//	arango::json doc2{{"name", "Jane Doe"}};
//	db.replace_document(doc0["_id"], doc2);

//	// Read document
//	doc1 = db.read_document(doc0["_id"]);
//	std::cout << doc1 << std::endl;

//	// Patch document
//	arango::json patch{{"iq", 100}};
//	db.patch_document(doc0["_id"], patch);

//	// Read document
//	doc1 = db.read_document(doc0["_id"]);
//	std::cout << doc1 << std::endl;

//	// Delete document
//	db.remove_document(doc0["_id"]);

//	// Read document
//	doc1 = db.read_document(doc0["_id"]);
//	std::cout << doc1 << std::endl;

//	// Create documents
//	arango::json p0{{"name", "John Doe"}};
//	db.create_document("persona", p0);
//	arango::json p1{{"name", "Jane Doe"}};
//	db.create_document("persona", p1);

//	// Create edge
//	arango::json e0{{"type", "in love"}};
//	db.create_edge("relation", e0, p0, p1);

//	// Read edge
//	arango::json e1 = db.read_document(e0["_id"]);
//	std::cout << e1 << std::endl;

//	// Replace edge
//	arango::json e2 = {{"type", "married"}};
//	db.patch_edge(e0["_id"], e2);

//	// Read edge
//	e1 = db.read_document(e0["_id"]);
//	std::cout << e1 << std::endl;

//	// Patch edge
//	arango::json edgePatch = {{"type", "in love"}};
//	db.patch_edge(e0["_id"], edgePatch);

//	// Read edge
//	e1 = db.read_document(e0["_id"]);
//	std::cout << e1 << std::endl;

//	// Delete edge
//	bool result = db.remove_edge(e0["_id"]);
//	std::cout << "Remove Edge: " << result << std::endl;

//	// Read edge
//	e1 = db.read_document(e0["_id"]);
//	std::cout << e1 << std::endl;

//	// Clean up
//	db.remove_document(p0["_id"]);
//	db.remove_document(p1["_id"]);


//	auto v = arango::json{{"name", "Karlskrona"}};
//	db.graph_create_vertex("gen-graph", "persona", v);

//	std::cout << v << std::endl;
//	auto a = db.graph_read_vertex("gen-graph", v["_id"].get<std::string>());
//	std::cout << a << std::endl;

//	auto v2 = arango::json{{"name", "Ronneby"}};
//	db.graph_replace_vertex("gen-graph", v["_id"], v2);
//	std::cout << v2 << std::endl;

//	auto v3 = arango::json{{"name", "Karlskorna"}, {"population", 60000}};
//	db.graph_patch_vertex("gen-graph", v["_id"], v3);
//	std::cout << v3 << std::endl;

//	auto b = db.graph_read_vertex("gen-graph", v["_id"].get<std::string>());
//	std::cout << b << std::endl;


	arango::graph_database db("http://localhost:8529", "gen", "gen", "gen", "gen-graph");

	auto r = db.create_collection(arango::json{{"name", "my_collection"}, {"username", "gen"}});
	std::cout << r << std::endl;

	r = db.drop_collection("my_collection");
	std::cout << r << std::endl;

	std::cout << db.truncate_collection("persona") << std::endl;


	auto c0 = arango::json{{"name", "Karlskrona"}};
	db.create_vertex("persona", c0);

	auto c1 = arango::json{{"name", "Göteborg"}};
	db.create_vertex("persona", c1);

	auto c2 = arango::json{{"name", "Lund"}};
	db.create_vertex("persona", c2);

	auto e0 = arango::json{{"distance", 250}};
	db.create_edge("relation", e0, c0, c1);

	auto e1 = arango::json{{"distance", 300}};
	db.create_edge("relation", e1, c1, c2);

	auto e2 = arango::json{{"distance", 200}};
	db.create_edge("relation", e2, c2, c0);




	//db.graph_remove_vertex("gen-graph", v["_id"]);

	// Query
//	for(int i = 0; i < 23; ++i) {
//		// Create document
//		arango::json doc0{{"name", "Jane Doe " + boost::lexical_cast<std::string>(i)}};
//		db.create_document("persona", doc0);

//	}

	auto cursor = db.query("FOR u IN persona SORT u.name RETURN u");

	for(auto &&doc : cursor) {
		std::cout << doc << std::endl;
	}

//	for(auto &&doc : cursor) {
//		std::cout << doc << std::endl;
//	}


}

