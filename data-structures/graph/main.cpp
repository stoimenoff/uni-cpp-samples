#include "graph.h"
#include "graphutils.h"

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

	string ver = "pesho";
	names.dottyPrint(std::cerr);
	// BFSInducedGraph(names, ver).dottyPrint(std::cerr);
	for (const auto& entry : allBFSInducedGraphs(names))
		entry.second.dottyPrint(std::cerr);

	for (const set<string>& layer : BFSInducedLayers(names, string("pesho")))
	{
		std::cout << "---------------------" << std::endl;
		for (const string& vertex : layer)
			std::cout << vertex << std::endl;
	}

	return 0;
}
