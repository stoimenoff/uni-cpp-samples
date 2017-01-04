#include "graph.h"
#include <string>
#include <iostream>

using std::string;

int main()
{
	Graph<string> names;
	names.addVertex("pesho");
	names.addVertex("gosho");
	names.addVertex("penka");
	names.addVertex("stamat");

	names.addEdge("pesho", "gosho");
	names.addEdge("stamat", "gosho");
	names.addEdge("pesho", "penka");
	names.addEdge("penka", "pesho");

	// names.deleteEdge("penka", "pesho");
	// names.deleteVertex("gosho");

	names.addVertex("kiro");
	names.addEdge("kiro", "penka");

	for (const string& vertex : names.getVertexes())
		std::cout << vertex << std::endl;

	names.dottyPrint(std::cerr);

	return 0;
}
