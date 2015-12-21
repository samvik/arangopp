#include <iostream>

#include "arango++/database.h"

int main(int argc, char **argv) {
	arango::database db("http://localhost:8529", "gen");

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




	// Query
//	for(int i = 0; i < 10; ++i) {
//		// Create document
//		arango::json doc0{{"name", "John Doe"}};
//		db.create_document("persona", doc0);

//		// Create document
//		arango::json doc1{{"name", "Jane Doe"}};
//		db.create_document("persona", doc1);
//	}

	auto cursor = db.query("FOR u IN persona RETURN u");

	std::cout << cursor.result() << std::endl;
	while(cursor.has_more()) {
		cursor.get_more();

		std::cout << cursor.result() << std::endl;

	}


}

