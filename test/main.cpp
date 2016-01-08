#include <iostream>
#include <boost/lexical_cast.hpp>
#include "arango++/graph_database.h"
#include "arango++/document_database.h"

int main(int argc, char **argv) {
	arango::document_database db("http://localhost:8529", "gen", "gen", "gen");
	arango::graph_database graph("http://localhost:8529", "gen", "gen", "gen", "gen-graph");

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


	std::cout << graph.create_vertex("persona",
																	 arango::json{{"name", "Karlskrona"}}) << std::endl;

//	std::cout << graph.read_vertex(v["_id"]) << std::endl;

//	auto v2 = arango::json{{"name", "Ronneby"}};
//	graph.replace_vertex(v["_id"], v2);
//	std::cout << v2 << std::endl;

//	auto v3 = arango::json{{"name", "Karlskorna"}, {"population", 60000}};
//	graph.patch_vertex(v["_id"], v3);
//	std::cout << v3 << std::endl;

//	std::cout << graph.read_vertex(v["_id"]) << std::endl;


	//std::cout << graph.list_collections() << std::endl;
//	std::cout << graph.create_collection(arango::json{{"name", "my_collection"}, {"username", "gen"}}) << std::endl;
//	std::cout << graph.get_collection("my_collection") << std::endl;
//	std::cout << graph.get_collection_properties("my_collection") << std::endl;
//	std::cout << graph.get_collection_count("my_collection") << std::endl;
//	std::cout << graph.get_collection_statisitcs("my_collection") << std::endl;
//	std::cout << graph.get_collection_revision_id("my_collection") << std::endl;
//	std::cout << graph.get_collection_checksum("my_collection") << std::endl;
//	std::cout << graph.drop_collection("my_collection") << std::endl;
	//std::cout << graph.truncate_collection("persona") << std::endl;


	auto c0 = graph.create_vertex("persona", arango::json{{"name", "Karlskrona"}});
	auto c1 = graph.create_vertex("persona", arango::json{{"name", "Göteborg"}});
	auto c2 = graph.create_vertex("persona", arango::json{{"name", "Lund"}});

	std::cout << graph.read_vertex(c1["_id"]) << std::endl;
	std::cout << "replace " << graph.replace_vertex(c1["_id"], arango::json{{"name", "Kalle Anka"}}) << std::endl;
	std::cout << "patch " << graph.patch_vertex(c1["_id"], arango::json{{"hello", "world"}}) << std::endl;
	std::cout << graph.read_vertex(c1["_id"]) << std::endl;

	std::cout << c0 << std::endl;
	std::cout << c1 << std::endl;
	std::cout << c2 << std::endl;

	auto e0 = graph.create_edge("relation", arango::json{{"distance", 250}}, c0, c1);
	auto e1 = graph.create_edge("relation", arango::json{{"distance", 300}}, c1, c2);
	auto e2 = graph.create_edge("relation", arango::json{{"distance", 200}}, c2, c0);

	std::cout << e0 << std::endl;
	std::cout << e1 << std::endl;
	std::cout << e2 << std::endl;

	std::cout << "remove " << graph.remove_vertex(c1["_id"]) << std::endl;




	//db.graph_remove_vertex("gen-graph", v["_id"]);

	// Query
//	for(int i = 0; i < 23; ++i) {
//		// Create document
//		arango::json doc0{{"name", "Jane Doe " + boost::lexical_cast<std::string>(i)}};
//		 db.create_document("persona", doc0);

//	}

//	auto cursor = graph.query("FOR u IN persona SORT u.name RETURN u");

//	for(auto &&doc : cursor) {
//		std::cout << doc << std::endl;
//	}

//	for(auto &&doc : cursor) {
//		std::cout << doc << std::endl;
//	}


}

