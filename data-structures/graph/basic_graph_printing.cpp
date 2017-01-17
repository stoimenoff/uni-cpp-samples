#include "graph.h"

#include <queue>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <iostream>

using std::queue;
using std::set;
using std::map;
using std::vector;
using std::list;
using std::cout;
using std::endl;

template <class T>
void printBFS(const Graph<T>& graph, const T& startingVertex)
{
	queue<T> vertexes;
	set<T> visited;
	vertexes.push(startingVertex);
	visited.insert(startingVertex);

	while (!vertexes.empty())
	{
		T currentVertex = vertexes.front();
		vertexes.pop();

		cout << currentVertex << endl;

		for (const T& adjecent : graph.getAdjacent(currentVertex))
		{
			if (visited.count(adjecent) == 0)
			{
				visited.insert(adjecent);
				vertexes.push(adjecent);
			}
		}
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

	printBFS(graph, 0);

	return 0;
}
