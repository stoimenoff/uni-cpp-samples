#ifndef _GRAPH_UTILS_H_
#define _GRAPH_UTILS_H_

#include "graph.h"
#include "../bucket/bucket.h"

#include <queue>
#include <set>
#include <map>
#include <vector>
#include <list>

using std::queue;
using std::set;
using std::map;
using std::vector;
using std::list;
using std::pair;

template <class T>
void addAdjacencyListToGraph(Graph<T>& graph, const list<T>& adjacencyList)
{
	auto it = adjacencyList.cbegin();
	T startingVertex = *it;
	if (!graph.containsVertex(startingVertex))
		graph.addVertex(startingVertex);

	for (++it; it != adjacencyList.cend(); ++it)
	{
		T adjacentVertex = *it;
		if (!graph.containsVertex(adjacentVertex))
			graph.addVertex(adjacentVertex);
		graph.addEdge(startingVertex, adjacentVertex);
	}
}

template <class T>
Graph<T> graphFromAdjacencyLists(const list<list<T>>& adjacencyLists)
{
	Graph<T> graph;
	for (const list<T>& adjacencyList : adjacencyLists)
		addAdjacencyListToGraph(graph, adjacencyList);
	return graph;
}

template <class T>
Graph<T> graphFromEdges(const list<pair<T, T>>& edges)
{
	Graph<T> graph;
	for (const pair<T, T>& edge : edges)
	{
		if (!graph.containsVertex(edge.first))
			graph.addVertex(edge.first);
		if (!graph.containsVertex(edge.second))
			graph.addVertex(edge.second);
		graph.addEdge(edge.first, edge.second);
	}
	return graph;
}

template <class ResultType, class VertexType>
class GraphBFSReducer
{
	public:
		virtual void nextVertex(const VertexType&) = 0;
		virtual void nextLayer() = 0;
		virtual ResultType getResult() = 0;
};

template <class ResultType, class T>
ResultType BFS(const Graph<T>& graph, const T& startingVertex,
			GraphBFSReducer<ResultType, T>& graphReducer)
{
	queue<Bucket<T>> vertexes;
	set<T> visited;
	vertexes.push(Bucket<T>());
	vertexes.push(Bucket<T>(startingVertex));
	visited.insert(startingVertex);

	while (vertexes.size() > 1)
	{
		if (!vertexes.front().hasData())
		{
			graphReducer.nextLayer();
			vertexes.pop();
			vertexes.push(Bucket<T>());
		}
		else
		{
			T currentVertex = vertexes.front().getData();
			vertexes.pop();
			graphReducer.nextVertex(currentVertex);
			for (const T& adjecent : graph.getAdjacent(currentVertex))
			{
				if (visited.count(adjecent) == 0)
				{
					visited.insert(adjecent);
					vertexes.push(Bucket<T>(adjecent));
				}
			}
		}
	}
	return graphReducer.getResult();
}

template <class T>
class BFSGraphReducer : public GraphBFSReducer<Graph<T>, T>
{
private:
	Graph<T> originalGraph;
	Graph<T> inducedGraph;
public:
	BFSGraphReducer(const Graph<T>& graph) : originalGraph(graph) {}
	virtual void nextVertex(const T& vertex)
	{
		if (!inducedGraph.containsVertex(vertex))
		{
			inducedGraph.addVertex(vertex);
		}
		for (const T& adjecent : originalGraph.getAdjacent(vertex))
		{
			if (!inducedGraph.containsVertex(adjecent))
			{
				inducedGraph.addVertex(adjecent);
				inducedGraph.addEdge(vertex, adjecent);
			}
		}
	}
	virtual void nextLayer() {}
	virtual Graph<T> getResult()
	{
		return inducedGraph;
	}
};

template <class T>
Graph<T> BFSInducedGraph(const Graph<T>& graph, const T& startingVertex)
{
	BFSGraphReducer<T> BFSGraphInducer(graph);
	return BFS<Graph<T>, T>(graph, startingVertex, BFSGraphInducer);
}

template <class T>
class BFSGraphLayerReducer : public GraphBFSReducer<vector<set<T>>, T>
{
private:
	vector<set<T>> layers;
public:
	virtual void nextVertex(const T& vertex)
	{
		layers.back().insert(vertex);
	}
	virtual void nextLayer()
	{
		layers.push_back(set<T>());
	}
	virtual vector<set<T>> getResult()
	{
		return layers;
	}
};

template <class T>
vector<set<T>> BFSInducedLayers(const Graph<T>& graph, const T& startingVertex)
{
	BFSGraphLayerReducer<T> layerReducer;
	return BFS<vector<set<T>>, T>(graph, startingVertex, layerReducer);
}

template <class T>
map<T, Graph<T>> allBFSInducedGraphs(const Graph<T>& graph)
{
	map<T, Graph<T>> graphs;
	for (const T& vertex : graph.getVertexes())
	{
		graphs[vertex] = BFSInducedGraph<T>(graph, vertex);
	}
	return graphs;
}

template <class T>
list<list<T>> allLimitedPaths(const Graph<T>& graph, const T& startingVertex,
							const T& endVertex, unsigned int limit)
{
	list<list<T>> resultPaths;
	list<list<T>> paths;
	list<T> currentPath;
	currentPath.push_back(startingVertex);
	paths.push_back(currentPath);

	unsigned int currentSize = 0;
	for (unsigned int i = 0; i <= limit; ++i)
	{
		currentSize = paths.size();
		for (unsigned int j = 0; j < currentSize; ++j)
		{
			currentPath = paths.front();
			paths.pop_front();
			if (currentPath.back() == endVertex)
				resultPaths.push_back(currentPath);
			for (const T& adjacent : graph.getAdjacent(currentPath.back()))
			{
				currentPath.push_back(adjacent);
				paths.push_back(currentPath);
				currentPath.pop_back();
			}
		}
	}

	return resultPaths;
}

#endif
