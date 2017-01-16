#include "graph.h"
#include "graphutils.h"

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

template <class T>
void printListOfLists(list<list<T>> lists)
{
	for (const list<T>& innerList : lists)
	{
		for (const T& element : innerList)
		{
			cout << element << " ";
		}
		cout << endl;
	}
}

int main()
{
	const int VETEXES_SIZE = 7;
	Graph<int> graph;
	for (int i = 0; i < VETEXES_SIZE; ++i)
	{
		graph.addVertex(i);
	}

	graph.addEdge(0, 2);
	graph.addEdge(0, 3);
	graph.addEdge(0, 4);
	graph.addEdge(3, 2);
	graph.addEdge(4, 2);
	graph.addEdge(4, 6);
	graph.addEdge(5, 2);
	graph.addEdge(5, 4);
	graph.addEdge(6, 5);

	printListOfLists(allLimitedPaths(graph, 0, 2, 15));

	return 0;
}
