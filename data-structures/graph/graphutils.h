#ifndef _GRAPH_UTILS_H_
#define _GRAPH_UTILS_H_

#include "graph.h"

#include <queue>
#include <set>
#include <map>

using std::queue;
using std::set;
using std::map;

template <class T>
Graph<T> BFSInducedGraph(const Graph<T>& graph, const T& startingVertex)
{
	Graph<T> inducedGraph;
	queue<T> vertexes;
	set<T> visited;
	vertexes.push(startingVertex);
	visited.insert(startingVertex);

	while (!vertexes.empty())
	{
		T currentVertex = vertexes.front();
		vertexes.pop();
		if (!inducedGraph.containsVertex(currentVertex))
			inducedGraph.addVertex(currentVertex);
		for (const T& adjecent : graph.getAdjacent(currentVertex))
		{
			if (!inducedGraph.containsVertex(adjecent))
			{
				inducedGraph.addVertex(adjecent);
				inducedGraph.addEdge(currentVertex, adjecent);
			}
			if (visited.count(adjecent) == 0)
			{
				visited.insert(adjecent);
				vertexes.push(adjecent);
			}
		}
	}
	return inducedGraph;
}

template <class T>
map<T, Graph<T>> allBFSInducedGraphs(const Graph<T>& graph)
{
	map<T, Graph<T>> graphs;
	for (const T& vertex : graph.getVertexes())
	{
		graphs[vertex] = BFSInducedGraph(graph, vertex);
	}
	return graphs;
}

#endif
