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

	Graph<int> bigOne;
	bigOne.addVertex(0);
	for (int i = 1; i < 100; ++i)
	{
		bigOne.addVertex(i);
		bigOne.addEdge(i, i-1);
	}
	bigOne.addEdge(0, 99);

	for (int i = 0; i < 100; ++i)
	{
		bigOne.addEdge(i, 99-i);
	}
	bigOne.dottyPrint(std::cerr);

	return 0;
}
